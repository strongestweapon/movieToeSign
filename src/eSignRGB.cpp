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

void eSignRGB::setPosition(int x,int y,int z)
{
    posX = x;
    posY = y;
    posZ = z;
}
void eSignRGB::setPosNetwork(int _posNetwork)
{
    posNetwork = _posNetwork;
}



int eSignRGB::getX() {
    return posX;
}
int eSignRGB::getY() {
    return posY;
}
int eSignRGB::getZ() {
    return posZ;
}
