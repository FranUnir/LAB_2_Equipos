🌦️ Sistema de Control y Actuación Climática
Este proyecto implementa una boya climática con Arduino que mide, controla y presenta condiciones meteorológicas clave. También actúa automáticamente sobre dispositivos como calefactor y compuerta de ventilación para mantener las baterías dentro de condiciones seguras.

🧠 Objetivo
Medir: temperatura, humedad, luz, aire, viento.

Controlar: calefactor (si Tbat < 22 °C) y servomotor (si Tbat > 40 °C).

Visualizar en LCD los datos ambientales y del sistema.

Simular de forma realista el comportamiento en Wokwi.

🧰 Hardware
🔌 Diagrama de Conexiones
🛠️ El diagrama será incluido en la siguiente sección como imagen Fritzing (.png).

📦 BOM (Bill of Materials)
Componente	Cant.	Descripción
Arduino UNO	1	Microcontrolador principal
DHT22	2	Sensor Tº y Hº (ambiente y batería)
LDR	1	Sensor de luz
Servo motor SG90	1	Control de compuerta de ventilación
Buzzer	1	Señal sonora nocturna
LED	1	Luz de señalización nocturna
Pantalla LCD I2C 16x2	1	Visualización de datos
Resistencias	Varios	Pull-up / divisores de tensión
Protoboard + cables	-	Conexionado

💻 Firmware
🧾 Código Fuente (comentado)
Consulta Lab_2.ino

Cambios relevantes:
🔥 Control de calefactor: ON si Tbat < 22°C, OFF si Tbat > 28°C.

🌬️ Nuevo: Servomotor conectado al pin D9 que abre compuerta si Tbat > 40°C.

🌃 Control nocturno de buzzer y LED cuando luz < 80%.

📺 Presentación cíclica de datos en LCD.

🧪 Debug serie completo y detallado.

🧪 Pruebas de Validación
Requisito	Estado
Medición de variables ambientales	✅
Control calefactor con zona muerta	✅
Control servo compuerta cuando Tbat > 40°C	✅
Visualización LCD y depuración serie	✅
Simulación funcional en Wokwi	✅

🔗 [Simulación en Wokwi](https://wokwi.com/projects/430770980504890369)
