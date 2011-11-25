#include "eSignRGBColumn.h"

eSignRGBColumn::eSignRGBColumn()
{
    columnColor = ofColor(0,0,0);
    portNumber =0;
}

eSignRGBColumn::~eSignRGBColumn()
{
    //dtor
}




void eSignRGBColumn::setup(float x, float y, int LEDNumber, bool direction, float rectSize)
{
    //1. save column x,y postion
    //2. instantiate LEDNumber of eSignRGB objects
    //3. assign z postion and network Postion of eSignRGB based on direction
    //4. push eSignRGB


    columnRect = ofRectangle(x,y,rectSize,rectSize);
    //UP: directon is true
    if (direction == true){
        for(int i = 0; i < LEDNumber;i++)
        {
            eSignRGB RGBLED;
            RGBLED.posZ = i;
            RGBLED.posNetwork = i;
            eSignRGBs.push_back(RGBLED);
        }
    }
    else //DOWN: direction is false
    {
        for(int i = 0; i < LEDNumber;i++)
        {
            eSignRGB RGBLED;
            RGBLED.posZ = i;
            RGBLED.posNetwork = LEDNumber-1-i;
            eSignRGBs.push_back(RGBLED);
        }
    }

}

void eSignRGBColumn::setColor(ofColor c)
{
    columnColor.r=c.r;
    columnColor.g=c.g;
    columnColor.b=c.b;
}

ofColor eSignRGBColumn::getColor()
{
    return columnColor;
}
