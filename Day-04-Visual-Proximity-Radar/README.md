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

## 🚀 How to Run
1. Install `Adafruit_GFX` and `Adafruit_SH110X` libraries via the Arduino Library Manager.
2. Wire up the hardware according to the configuration matrix above.
3. Flash the code to your ESP32 board.