# 📏 Day 04: Visual Proximity Radar

A simple and clean car-dashboard-style parking assistant system built with ESP32, an HC-SR04 ultrasonic sensor, and an SH1106 OLED display configured in portrait layout.

## 🛠️ Project Features
- **Portrait UI Layout:** The display is rotated 90 degrees to work like a vertical radar screen.
- **Dynamic Progress Bar:** A visual bar that fills up from bottom to top as objects get closer to the sensor.
- **Zone Alerts:** Real-time distance status updates:
  - `SAFE`: Distance > 50cm
  - `WARN`: Distance between 20cm and 50cm
  - `STOP!`: Distance < 20cm (Critical range)

## 📐 Circuit Configuration

| Component | Pin | ESP32 Pin | Description |
| :--- | :--- | :--- | :--- |
| **HC-SR04** | VCC | Vin (5V) | Power supply |
| **HC-SR04** | GND | GND | Ground |
| **HC-SR04** | Trig | GPIO 25 | Trigger pulse output |
| **HC-SR04** | Echo | GPIO 26 | Echo return input |
| **SH1106 OLED**| VCC | 3.3V | Display power |
| **SH1106 OLED**| GND | GND | Ground |
| **SH1106 OLED**| SDA | GPIO 21 | I2C Data Line |
| **SH1106 OLED**| SCL | GPIO 22 | I2C Clock Line |

## 📸 Working Demo
<div align="center">
  <img src="./assets/working_demo.gif" width="400" style="border-radius: 10px;" alt="OLED Demo">
  <p><i>The OLED display showing dynamic Temperature and Humidity readings.</i></p>
</div>

## 🚀 How to Run
1. Install `Adafruit_GFX` and `Adafruit_SH110X` libraries via the Arduino Library Manager.
2. Wire up the hardware according to the configuration matrix above.
3. Flash the code to your ESP32 board.

## 💻 Source Code
<details>
<summary>Click to view code</summary>

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 25; 
const int echoPin = 26; 

long duration;
int distance;
int lastValidDistance = 0;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if(!display.begin(i2c_Address, true)) {
    for(;;);
  }

  display.clearDisplay();
  display.setRotation(1);
  display.display();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.034 / 2;

  if (distance > 2 && distance < 400) {
    lastValidDistance = distance; 
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 5);
  display.println("RADAR");
  display.drawLine(0, 15, 64, 15, SH110X_WHITE);

  display.setTextSize(2);
  display.setCursor(5, 30);
  display.print(lastValidDistance);
  display.setTextSize(1);
  display.print("cm");

  int barHeight = map(constrain(lastValidDistance, 0, 100), 0, 100, 60, 0); 
  display.drawRect(20, 60, 24, 62, SH110X_WHITE); 
  display.fillRect(22, 60 + (60 - barHeight), 20, barHeight, SH110X_WHITE); 

  display.setTextSize(1);
  display.setCursor(5, 120);
  if(lastValidDistance < 20) {
    display.print("STOP!");
  }
  else if(lastValidDistance < 50) {
    display.print("WARN");
  }
  else {
    display.print("SAFE");
  }

  display.display();
  delay(60);
}