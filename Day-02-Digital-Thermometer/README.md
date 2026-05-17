<div align="center">
  <img src="https://img.shields.io/badge/Day-02%2F30-blueviolet?style=for-the-badge&logo=calendar" />
  <img src="https://img.shields.io/badge/Hardware-ESP32-red?style=for-the-badge&logo=esphome" />
  <img src="https://img.shields.io/badge/Status-Completed-success?style=for-the-badge" />

  <h1>🌡️ Day 2: ESP32 Digital Thermometer (DHT22)</h1>
  <p>Precision temperature and humidity monitoring with local library integration.</p>
</div>

---

## 📝 Project Overview
On the second day of my challenge, I implemented a high-precision digital thermometer using the **ESP32** and the **DHT22** sensor. Unlike Day 1, today's project involves one-wire communication protocols and processing float-point sensor data.

### ✨ Key Features
* **High Precision:** Utilizing DHT22 for ±0.5°C accuracy.
* **Portable Code:** Library files (`DHT22.h` & `DHT22.cpp`) are included directly in the source folder for easy compilation.
* **Error Handling:** Integrated check for sensor communication status.

---

## 📸 Working Demo
<div align="center">
  <img src="./assets/working_demo.gif" width="500" style="border-radius: 10px;" alt="DHT22 Sensor Output">
  <p><i>Real-time environment monitoring on Serial Monitor.</i></p>
</div>

---

## 📐 Circuit Diagram
* **VCC:** 3.3V (ESP32)
* **GND:** GND (ESP32)
* **Data Pin:** GPIO 15 (ESP32)

> 📌 **Note:** If using a bare DHT22 sensor (not a module), ensure a 10kΩ pull-up resistor is connected between VCC and Data pins.

---

## 💻 Source Code
<details>
<summary>Click to expand source code</summary>

```cpp
#include "DHT22.h" 

#define pinDATA 15 
DHT22 dht22(pinDATA);

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(2000); 
  float t = dht22.getTemperature();
  float h = dht22.getHumidity();

  if (dht22.getLastError() == dht22.OK) {
    Serial.print("Temp: "); Serial.print(t);
    Serial.print("C | Humidity: %"); Serial.println(h);
  }
}