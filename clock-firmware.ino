#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <WiFi.h>
#include "time.h"

#define TFT_CS 20
#define TFT_RST 8
#define TFT_DC 2
#define TFT_SCLK 6
#define TFT_MOSI 7

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// network credentials
const char* ssid = "";
const char* password = "";

// NTP server and timezone configuration
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600; // timezone offset in seconds
const int daylightOffset_sec = 3600; // 3600 if daylight savings applies otherwise 0

// pin definitions
const int buzzerPin = 0;
const int buttonPins[] = { 1, 3, 4, 5 };

// alarm settings (24-hour format)
const int alarmHour = 6;
const int alarmMinute = 0;

// state tracking
bool alarmActive = false;
bool alarmTriggeredToday = false;
int lastDisplayedMinute = -1;

void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  for (int i=0; i<4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  tft.init(284, 76);
  tft.setRotation(2);
  Serial.println("TFT Initialized!");

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.print("Connecting WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,0);
  tft.print("Fetching time...");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0,0);
    tft.print("Time error");
  } else {
    Serial.println("Time synchronized successfuly");
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0,0);
    tft.print("Ready");
  }
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    delay(1000);
    return;
  }

  if (timeinfo.tm_min != lastDisplayedMinute && !alarmActive) {
    lastDisplayedMinute = timeinfo.tm_min;
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0,0);
    tft.print(timeinfo.tm_hour);
    tft.print(":");
    if (timeinfo.tm_min < 10) tft.print("0");
    tft.print(timeinfo.tm_min);
  }

  if (timeinfo.tm_hour == alarmHour && timeinfo.tm_min == alarmMinute) {
    if (!alarmTriggeredToday && !alarmActive) {
      alarmActive = true;
      alarmTriggeredToday = true;
      Serial.println("Alarm triggered");
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(0,0);
      tft.print("Wake up!");
    } 
  } else {
      alarmTriggeredToday = false;
  }

  if (alarmActive) {
    digitalWrite(buzzerPin, HIGH);

    for (int i=0; i<4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        alarmActive = false;
        digitalWrite(buzzerPin, LOW);
        Serial.println("Alarm stopped by button press");
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(0,0);
        tft.print("Good morning!");
        break;
      }
    }
  }

  delay(200);
}
