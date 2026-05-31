#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "time.h" // ESP32'nin yerleşik zaman kütüphanesi

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Wi-Fi credentials
const char* ssid     = "SUPERONLINE_WiFi_1BB0";
const char* password = "Mete2000*";

// NTP Sunucu Ayarları
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 10800; // UTC+3 için 3 saat x 3600 saniye = 10800
const int   daylightOffset_sec = 0; // Sabit saat uygulaması nedeniyle 0

void setup() {
  Serial.begin(115200);

  // OLED Setup
  display.begin(i2c_Address, true);
  display.setRotation(2); 
  display.clearDisplay();

  // Connect to Wi-Fi
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(8, 15);
  display.print("Connecting to Wi-Fi...");
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Zamanı NTP sunucusundan yapılandır
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  display.clearDisplay();
  display.setCursor(8, 15);
  display.println("Wi-Fi Connected!");
  display.setCursor(8, 35);
  display.println("Syncing Time...");
  display.display();
  delay(2000);
}

void loop() {
  struct tm timeinfo;
  // Zaman bilgisini başarıyla alamazsa loop'u tekrar başlat (Hatalı tarihi engeller)
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    delay(100);
    return;
  }

  // Zaman ve Tarih karakter dizilerini hazırla
  char timeString[9];  // HH:MM:SS
  char dateString[11]; // DD/MM/YYYY

  strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);
  strftime(dateString, sizeof(dateString), "%d/%m/%Y", &timeinfo);

  // Render Dashboard
  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, SH110X_WHITE); // Şık çerçeve

  // Header
  display.setTextSize(1);
  display.setCursor(8, 6);
  display.println("INTERNET CLOCK (NTP)");
  display.drawLine(4, 16, 124, 16, SH110X_WHITE);

  // Time Display
  display.setTextSize(2);
  display.setCursor(18, 24);
  display.println(timeString);

  // Date Display
  display.setTextSize(1);
  display.setCursor(32, 48);
  display.println(dateString);

  display.display();
  delay(1000); // Saniyede bir ekranı güncelle
}