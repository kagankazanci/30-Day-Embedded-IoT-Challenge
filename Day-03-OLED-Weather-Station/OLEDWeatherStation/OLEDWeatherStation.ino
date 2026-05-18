#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "DHT22.h"

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT22 dht22(15);

void setup() {
  Serial.begin(115200);

  if(!display.begin(i2c_Address, true)) {
    Serial.println(F("SH1106 not found!"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 25);
  display.println("WEATHER STATION");
  display.display();
  delay(2000);
}

void loop() {
  delay(2000);

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();

  display.clearDisplay();

  if (dht22.getLastError() != dht22.OK) {
    display.setCursor(0, 0);
    display.println("Sensor Error!");
  } else {

    display.setTextSize(1);
    display.setCursor(20, 0);
    display.println("--- DAY 03 ---");
    display.drawLine(0, 10, 128, 10, SH110X_WHITE);


    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print("T: ");
    display.print(t, 1);
    display.print(" C");

    display.setCursor(0, 45);
    display.print("H: %");
    display.print(h, 1);
  }

  display.display();
}