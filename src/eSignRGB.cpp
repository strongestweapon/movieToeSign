#include "eSignRGB.h"

eSignRGB::eSignRGB()
{
    LEDColor.r=0;
    LEDColor.g=0;
    LEDColor.b=0;
}

eSignRGB::~eSignRGB()
{
    //dtor
}

void eSignRGB::setColor(ofColor c)
{
    LEDColor = c;
}


ofColor eSignRGB::getColor()
{
    return LEDColor;
}
