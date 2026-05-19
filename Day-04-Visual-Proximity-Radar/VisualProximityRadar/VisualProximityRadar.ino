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