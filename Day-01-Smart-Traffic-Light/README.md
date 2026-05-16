<div align="center">
  <img src="https://img.shields.io/badge/Day-01%2F30-blueviolet?style=for-the-badge&logo=calendar" />
  <img src="https://img.shields.io/badge/Hardware-ESP32-red?style=for-the-badge&logo=esphome" />
  <img src="https://img.shields.io/badge/Status-Completed-success?style=for-the-badge" />

  <h1>🚦 ESP32 Smart Traffic Light System</h1>
  <p>First day of the challenge: Learning GPIO inputs and outputs.</p>
</div>

---

## 📝 Project Description
Today's project focuses on controlling multiple outputs (LEDs) based on a digital input (Push Button). The system mimics a real-world traffic light: it stays green for vehicles until a pedestrian requests to cross by pressing the button.

## 📸 Working Demo
<div align="center">
  <img src="./assets/working_demo.gif" width="500" style="border-radius: 10px;" alt="Project Demo">
</div>

## 📐 Circuit Connection (GPIO)
* **Red LED:** GPIO 23
* **Yellow LED:** GPIO 22
* **Green LED:** GPIO 21
* **Push Button:** GPIO 4 (with 10kΩ Pull-down resistor)

---

## 💻 Simple Source Code
<details>
<summary>Click to view the ESP32 Code</summary>

```cpp
// ESP32 Pin Definitions
const int LED_RED    = 23; 
const int LED_YELLOW = 22; 
const int LED_GREEN  = 21; 
const int BTN_PEDS   = 4;  

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BTN_PEDS, INPUT);
}

void loop() {
  // Default State: Green light for vehicles
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);

  // Check if pedestrian button is pressed
  if (digitalRead(BTN_PEDS) == HIGH) {
    delay(500); // Debounce delay
    
    // Switch to Yellow
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    delay(2000); 

    // Switch to Red (Pedestrians can cross)
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    delay(5000);

    // Transition back to Green
    digitalWrite(LED_YELLOW, HIGH);
    delay(1000);
  }
}