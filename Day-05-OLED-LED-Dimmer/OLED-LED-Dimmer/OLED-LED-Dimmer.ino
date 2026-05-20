#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1);

const int ledPin = 2;
const int pwmChannel = 0;
const int freq = 5000;
const int resolution = 8;

int brightness = 0;
bool fadingIn = true;

void setup() {
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ledPin, pwmChannel);

  display.begin(i2c_Address, true);
  display.setRotation(1);
  display.clearDisplay();
}

void loop() {
  ledcWrite(pwmChannel, brightness);

  int percent = map(brightness, 0, 255, 0, 100);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 5);
  display.println("PWM UI");
  display.drawLine(0, 15, 64, 15, SH110X_WHITE);

  display.setTextSize(2);
  display.setCursor(5, 45);
  display.print("%");
  display.print(percent);

  int barHeight = map(percent, 0, 100, 0, 50);
  display.drawRect(15, 110, 34, 10, SH110X_WHITE); 
  display.fillRect(17, 112, barHeight * 0.6, 6, SH110X_WHITE);

  display.display();

  if (fadingIn) {
    brightness += 5;
    if (brightness >= 255) fadingIn = false;
  } else {
    brightness -= 5;
    if (brightness <= 0) fadingIn = true;
  }

  delay(30);
}