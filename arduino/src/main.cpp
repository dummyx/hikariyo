#include <M5Stack.h>

#include <WiFi.h>
#include <ESP32Ping.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include "main.h"
#include "https.h"
#include "env.h"
#include "light.h"

#include "settings.h"


const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

bool isAtHome, isLightOn;
int command;
struct envValues env;
uint8_t counter = 0;

const IPAddress SMARTPHONE_IP;

// For RE0208 remote control CH1


uint32_t kBaudRate = 115200;

struct dataPacket {

};

uint16_t lightValue;



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

  Serial.begin(kBaudRate, SERIAL_8N1);
  initEnv();
  initIr();

  pinMode(LIGHT_READ_PIN, INPUT);

  setClock();
}

void show(String s)
{
  M5.Lcd.println(s);
  Serial.println(s);
}

void loop()
{
  lightValue = readLight();
  isLightOn = checkLight(lightValue);
  env = readEnv();

  // isLightOn ? fakeGet(SET_ON_URL) : fakeGet(SET_OFF_URL);

  command = fakeGet(GET_COMMAND_URL);
  if (command == 221)
  {
    turnLight();
  }
  else if (isLightOn)
  {
    isAtHome = Ping.ping(remote_ip);
    if (!isAtHome)
    {
      show(String("Light left on, turning off"));
      turnLight();
    }
  }

  Serial.printf("%f, %f, %f\n", env.temperature, env.humidity, env.pressure);

  counter++;
  if (counter > 20  ) {
    uploadData(lightValue, env.temperature, env.humidity, env.pressure);
  }
  delay(2000);
}

void uploadData(uint16_t light, float temp, float humi, float pres) {
  char uploadUrl[200];
  sprintf(uploadUrl, UPLOAD_DATA_URL, light, temp, humi, pres);
  fakeGet(uploadUrl);
}
