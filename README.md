# 🌦️ Sistema de Control y Actuación Climática

Este proyecto implementa una **boya climática con Arduino** diseñada para **medir, controlar y presentar condiciones meteorológicas clave**. Además, actúa automáticamente sobre dispositivos como un calefactor y una compuerta de ventilación para **mantener las baterías dentro de rangos de temperatura seguros**.

-----

## 🧠 Objetivo

El objetivo principal de este sistema es:

  * **Medir**: Temperatura, humedad, luz ambiental y de viento.
  * **Controlar**:
      * **Calefactor**: Se activa si la temperatura de la batería ($T\_{bat}$) es inferior a $22^\\circ C$.
      * **Servomotor**: Abre la compuerta de ventilación si la temperatura de la batería ($T\_{bat}$) supera los $40^\\circ C$.
  * **Visualizar**: Mostrar los datos ambientales y del sistema en una pantalla LCD.
  * **Simular**: Recrear de forma realista el comportamiento del sistema en Wokwi.

-----

## 🧰 Hardware

-----

### 🔌 Diagrama de Conexiones

-----

### 📦 BOM (Bill of Materials)

| Componente            | Cant. | Descripción                               |
| :-------------------- | :---- | :---------------------------------------- |
| Arduino UNO           | 1     | Microcontrolador principal                |
| DHT22                 | 2     | Sensor Tº y Hº (ambiente y batería)       |
| LDR                   | 1     | Sensor de luz                             |
| Servo motor SG90      | 1     | Control de compuerta de ventilación       |
| Buzzer                | 1     | Señal sonora nocturna                     |
| LED                   | 1     | Luz de señalización nocturna              |
| Pantalla LCD I2C 16x2 | 1     | Visualización de datos                    |
| Resistencias          | Varios | Pull-up / divisores de tensión            |
| Protoboard + cables   | -     | Conexionado                               |

-----

## 💻 Firmware

-----

### 🧾 Código Fuente (comentado)

Consulta el archivo [`Lab_2.ino`](https://www.google.com/search?q=./Lab_2.ino) para revisar el código fuente completo y comentado.

-----

### Cambios Relevantes en el Firmware:

  * **🔥 Control de Calefactor**: Se activa si la temperatura de la batería ($T\_{bat}$) es menor de $22^\\circ C$ y se desactiva si supera los $28^\\circ C$ (zona muerta para evitar oscilaciones).
  * **🌬️ Servomotor**: **Nuevo** control de servomotor (conectado al pin D9) que abre la compuerta de ventilación si la temperatura de la batería ($T\_{bat}$) es mayor de $40^\\circ C$.
  * **🌃 Control Nocturno**: Activación automática del buzzer y LED cuando el nivel de luz es inferior al $80%$.
  * **📺 Presentación LCD**: Visualización cíclica y organizada de todos los datos en la pantalla LCD.
  * **🧪 Debug Serie**: Implementación de un sistema de depuración completo y detallado a través del puerto serie.

-----

## 🧪 Pruebas de Validación

| Requisito                                  | Estado |
| :----------------------------------------- | :----- |
| Medición de variables ambientales          | ✅     |
| Control calefactor con zona muerta         | ✅     |
| Control servo compuerta cuando $T\_{bat} \> 40^\\circ C$ | ✅     |
| Visualización LCD y depuración serie       | ✅     |
| Simulación funcional en Wokwi              | ✅     |

-----

## 🔗 Simulación en Wokwi

Puedes ver y probar la simulación del proyecto directamente en Wokwi:

[**Acceder a la Simulación en Wokwi**](https://wokwi.com/projects/430770980504890369)

-----
