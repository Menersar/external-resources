#include "scratch_tcs3200.h"

Scratch_tcs3200::Scratch_tcs3200(uint8_t s2, uint8_t s3, uint8_t s0, uint8_t s1, uint8_t oe)
{
    device = new MD_TCS230(s2, s3, s0, s1, oe);
}

void Scratch_tcs3200::begin()
{
    device->begin();
}

void Scratch_tcs3200::calibrateWhite()
{
    device->read();
    while(!device->available())
        ;
    device->getRaw(&sd);
    device->setWhiteCal(&sd);
}

void Scratch_tcs3200::calibrateBlack()
{
    device->read();
    while(!device->available())
        ;
    device->getRaw(&sd);
    device->setDarkCal(&sd);
}

void Scratch_tcs3200::mesureColor()
{
    device->read();
    while(!device->available())
        ;
    device->getRGB(&rgb);
}

uint32_t Scratch_tcs3200::getColorValue(uint8_t color)
{
    if (color == TCS3200_RED)
    {
        return rgb.value[TCS230_RGB_R];
    }
    else if (color == TCS3200_GREEN)
    {
        return rgb.value[TCS230_RGB_G];
    }
    else if (color == TCS3200_BLUE)
    {
        return rgb.value[TCS230_RGB_B];
    }
    else
    {
        return ((uint32_t)rgb.value[TCS230_RGB_R] << 16) + ((uint32_t)rgb.value[TCS230_RGB_G] << 8) + rgb.value[TCS230_RGB_B];
    }
}
