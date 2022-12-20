#include <M5Stack.h>

#include <IRsend.h>
#include <WiFi.h>
#include <ESP32Ping.h>

#include <IRremoteESP8266.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include "main.h"
#include "https.h"

#include "settings.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

bool isAtHome, isLightOn;
int command;

const IPAddress SMARTPHONE_IP;

// For RE0208 remote control CH1
uint64_t switchData = 0x41B6D52A;
uint64_t fullLightData = 0x41B6659A;

IRsend irsend(IR_SEND_PIN);

uint32_t kBaudRate = 115200;

uint16_t lightThreshold = 2300;

void setup()
{
  M5.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    M5.Lcd.print('.');
  }
  M5.Lcd.print("connected");

  irsend.begin();
  Serial.begin(kBaudRate, SERIAL_8N1);

  pinMode(LIGHT_READ_PIN, INPUT);

  setClock();
}

void loop()
{
  isAtHome = Ping.ping(remote_ip);
  isLightOn = checkLight();

  if (isLightOn)
  {
    fakeGet(SET_ON_URL);
  }
  else
  {
    fakeGet(SET_OFF_URL);
  }

  command = fakeGet(GET_COMMAND_URL);
  if (command == 221)
  {
    if (isLightOn)
    {
      turnLightOff();
    }
    else
    {
      turnLightOn();
    }
  }
  else
  {
    if (!isAtHome && isLightOn)
    {
      show(String("Light left on, turning off"));
      turnLightOff();
    }
  }

  delay(1000);
}

void turnLightOff()
{
  show(String("Turning light off."));
  irsend.sendNEC(switchData);
}

void turnLightOn()
{
  irsend.sendNEC(fullLightData);
  show(String("Turning light on."));
}

void show(String s)
{
  M5.Lcd.println(s);
  Serial.println(s);
}

bool checkLight()
{
  // The brighter the lower.
  return analogRead(LIGHT_READ_PIN) < lightThreshold;
}