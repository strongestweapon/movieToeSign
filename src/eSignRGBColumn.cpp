#include "eSignRGBColumn.h"

eSignRGBColumn::eSignRGBColumn()
{
    columnColor = ofColor(0,0,0);
    portNumber =0;
    columnRect = ofRectangle(0,0,20,20);
}

eSignRGBColumn::~eSignRGBColumn()
{
    //dtor
}

void eSignRGBColumn::setup(float x, float y, int LEDNumber, bool direction, int rectSize)
{
    //1. save column x,y postion
    //2. instantiate LEDNumber of eSignRGB objects
    //3. assign z postion and network Postion of eSignRGB based on direction
    //4. push eSignRGB


    columnRect = ofRectangle(x,y,rectSize,rectSize);
    //UP: directon is true


    for(int i = 0; i < LEDNumber;i++)
    {
        eSignRGB RGBLED;
        RGBLED.setPosition(x,y,i);
        if (direction == true) {
            RGBLED.setPosNetwork(i);
        }else {
            RGBLED.setPosNetwork(LEDNumber-1-i);
        }
        eSignRGBs.push_back(RGBLED);
    }
}

void eSignRGBColumn::setColor(ofColor c)
{
    columnColor = c;

    for(int i =0; i < eSignRGBs.size();i++)
    {
        eSignRGBs[i].setColor(c);
    }
}

ofColor eSignRGBColumn::getColor()
{
    return columnColor;
}

int eSignRGBColumn::getNumOfLED()
{
    return eSignRGBs.size();
}
