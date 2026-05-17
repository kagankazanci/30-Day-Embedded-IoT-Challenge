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