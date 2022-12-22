#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <M5Stack.h>
#include <settings.h>
#include <main.h>

uint64_t switchData = 0x41B6D52A;
uint64_t fullLightData = 0x41B6659A;
IRsend irsend(IR_SEND_PIN);


void initIr() {
    irsend.begin();
}


void turnLight()
{
  show(String("Switching"));
  irsend.sendNEC(switchData);
}

bool checkLight(uint16_t rawValue) {
    return rawValue < LIGHT_THRESHOLD;
}


uint16_t readLight()
{
  return analogRead(LIGHT_READ_PIN);
}