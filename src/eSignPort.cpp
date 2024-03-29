#include "eSignPort.h"

eSignPort::eSignPort()
{
    portLEDNumber = 0;
    columnRectSize = 20;
}

eSignPort::~eSignPort()
{
    //dtor
}

void eSignPort::addColumn(float x, float y, int LEDNumber, bool direction)
{

    //2. instantiate a column
    //3. setup column based on inputs from gui and formerly added number of columns
    //4. push column object to eSignFixture
    eSignRGBColumn column;
    column.setup(x, y, LEDNumber, direction, columnRectSize);
    eSignRGBColumns.push_back(column);
    //bAddColumn = false;

}

void eSignPort::setColor(ofColor c)
{
    for(int i = 0; i < eSignRGBColumns.size(); i++)
    {
        eSignRGBColumns[i].setColor(c);
    }
}

int eSignPort::getNumOfeSignRGB()
{
    portLEDNumber = 0;
    for(int i = 0; i < eSignRGBColumns.size(); i++)
    {
        portLEDNumber = portLEDNumber + eSignRGBColumns[i].eSignRGBs.size();
    }
    return portLEDNumber;
}
