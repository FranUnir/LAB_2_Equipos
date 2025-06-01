#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- Definición de pines ---
#define DHTPIN 7              // Sensor ambiente
#define DHTBATPIN 8           // Sensor batería
#define DHTTYPE DHT22
#define LDR_PIN A0            // Sensor de luz (LDR)
#define AIR_PIN A1            // Sensor calidad de aire
#define WIND_SPEED_PIN A2     // Sensor velocidad del viento
#define WIND_DIR_PIN A3       // Sensor dirección del viento

#define LED_PIN 3             // LED señalización nocturna
#define BUZZER_PIN 5          // Buzzer señal sonora nocturna
#define HEATER_PIN 6          // Simulación calefactor con LED
#define SERVO_PIN 9           // Servo motor para compuerta de aire

// --- Inicialización de dispositivos ---
DHT dht(DHTPIN, DHTTYPE);
DHT dhtBat(DHTBATPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoCompuerta;

unsigned long lastBeepTime = 0;
bool buzzerState = false;

// --- Setpoints y zona muerta para control ---
const float TEMP_SETPOINT = 25.0;
const float HUM_SETPOINT = 80.0;
const float TEMP_DEADZONE = 3.0;
const float TEMP_OVERHEAT = 40.0;  // Umbral para compuerta aire

void setup() {
  Serial.begin(9600);
  dht.begin();
  dhtBat.begin();
  lcd.init();
  lcd.backlight();

  pinMode(LED_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  servoCompuerta.attach(SERVO_PIN);

  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // --- Lectura de sensores ---
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float tempBat = dhtBat.readTemperature();

  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Err sensor clima");
    return;
  }
  if (isnan(tempBat)) {
    lcd.setCursor(0, 0);
    lcd.print("Err sensor bat");
    return;
  }

  int luz = analogRead(LDR_PIN);
  int luzPct = map(luz, 0, 1023, 100, 0);
  int airePct = map(analogRead(AIR_PIN), 0, 1023, 0, 100);
  int vientoVel = map(analogRead(WIND_SPEED_PIN), 0, 1023, 0, 100);
  int vientoDir = map(analogRead(WIND_DIR_PIN), 0, 1023, 0, 360);

  // --- Control iluminación y sonido nocturno ---
  unsigned long now = millis();
  if (luzPct < 70) {
    if (now - lastBeepTime >= (buzzerState ? 100 : 400)) {
      buzzerState = !buzzerState;
      lastBeepTime = now;
      if (buzzerState) {
        tone(BUZZER_PIN, 1000);
        analogWrite(LED_PIN, 255);
      } else {
        noTone(BUZZER_PIN);
        analogWrite(LED_PIN, 0);
      }
    }
  } else {
    noTone(BUZZER_PIN);
    analogWrite(LED_PIN, 0);
  }

  // --- Control calefactor con zona muerta ---
  float upperLimit = TEMP_SETPOINT + TEMP_DEADZONE;
  float lowerLimit = TEMP_SETPOINT - TEMP_DEADZONE;

  if (tempBat < lowerLimit) {
    digitalWrite(HEATER_PIN, HIGH);
  } else if (tempBat > upperLimit) {
    digitalWrite(HEATER_PIN, LOW);
  }

  // --- Control de servo motor de compuerta ---
  if (tempBat > TEMP_OVERHEAT) {
    servoCompuerta.write(90);  // Abrir compuerta
  } else {
    servoCompuerta.write(0);   // Cerrar compuerta
  }

  // --- Mostrar en LCD ---
  mostrarLCD(temp, hum, luzPct, airePct, vientoVel, vientoDir, tempBat);

  // --- Debug serie ---
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" Hum: "); Serial.print(hum);
  Serial.print(" Luz: "); Serial.print(luzPct);
  Serial.print(" Aire: "); Serial.print(airePct);
  Serial.print(" Vv: "); Serial.print(vientoVel);
  Serial.print(" Dir: "); Serial.print(vientoDir);
  Serial.print(" Tbat: "); Serial.print(tempBat);
  Serial.print(" Heater: "); Serial.print(digitalRead(HEATER_PIN) ? "ON" : "OFF");
  Serial.print(" Comp: "); Serial.println(tempBat > TEMP_OVERHEAT ? "Abierta" : "Cerrada");

  delay(1000);
}

void mostrarLCD(float temp, float hum, int luz, int aire, int vv, int dir, float tempBat) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temp, 1); lcd.print((char)223); lcd.print("C H:"); lcd.print(hum, 0); lcd.print("%");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luz:"); lcd.print(luz); lcd.print("% Aire:"); lcd.print(aire); lcd.print("%");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vv:"); lcd.print(vv); lcd.print("km/h");
  lcd.setCursor(0, 1);
  lcd.print("Dir:"); lcd.print(dir); lcd.print((char)223);
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tbat:"); lcd.print(tempBat, 1); lcd.print((char)223); lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Heater:"); lcd.print(tempBat < TEMP_SETPOINT ? "ON " : "OFF");
  delay(1500);
}
