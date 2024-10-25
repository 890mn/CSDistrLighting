#include "gy30.h"
#include "main.h"

void initGY30() {
    Wire.begin(21, 19);

    Wire.beginTransmission(GY30_ADDRESS);
    Wire.write(0x01);
    Wire.endTransmission();

    Wire.beginTransmission(GY30_ADDRESS);
    Wire.write(0x07);
    Wire.endTransmission();

    Wire.beginTransmission(GY30_ADDRESS);
    Wire.write(0x10);
    Wire.endTransmission();
}

float updateGY30() {
    uint16_t data = 0;
    Wire.requestFrom(GY30_ADDRESS, 2);
    if (Wire.available() == 2)
    {
        data = Wire.read();
        data <<= 8;
        data |= Wire.read();
    }
    return data / 1.2;
}