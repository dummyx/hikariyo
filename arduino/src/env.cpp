#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

#include "env.h"

Adafruit_BMP280 bme;

void initEnv()
{
    Wire.begin(21, 22, 100000);
    bme.begin(0x76);
}

struct envValues readEnv()
{
    struct envValues values;

    static const uint8_t kSht30Addr = 0x44;

    unsigned int data[6];

    Wire.beginTransmission(kSht30Addr);

    Wire.write(0x2C);
    Wire.write(0x06);

    Wire.endTransmission();
    delay(500);

    Wire.requestFrom(kSht30Addr, 6);

    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();

    values.temperature = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
    values.humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
    values.pressure = bme.readPressure() * 0.01;

    return values;
}