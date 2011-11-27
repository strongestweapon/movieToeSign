#include "eSignFixture.h"

eSignFixture::eSignFixture()
{
    UDPAddress="";
    fixtureColor = ofColor(0,0,0);

}

eSignFixture::~eSignFixture()
{
    //dtor
}

void eSignFixture::setup(string address,int numOfPorts)
{
    UDPAddress = address;

    for(int i = 0; i < numOfPorts ; i++)
    {
        addPort();
    }
}

void eSignFixture::addColumn(int portNumber, float x, float y, int LEDNumber, bool direction)
{

    eSignPorts[portNumber].addColumn(x,y,LEDNumber,direction);
}


void eSignFixture::addPort()
{
    eSignPort port;
    //port.borderColor=ofColor(255% (int)eSignPorts.size());
    eSignPorts.push_back(port);

}


void eSignFixture::setColor(ofColor c)
{

    for(int i =0; i< eSignPorts.size(); i++)
    {
        eSignPorts[i].setColor(c);
    }
}

void eSignFixture::setColumnRectSize(int size)
{
    for(int i = 0; i <eSignPorts.size(); i++)
    {
        eSignPorts[i].setColumnRectSize(size);
    }
}

ofColor eSignFixture::getColor()
{
    return fixtureColor;
}





//void eSignFixture::addColumn(int LEDNumber, bool direction)
//{
//
//    //2. instantiate a column
//    //3. setup column based on inputs from gui and formerly added number of columns
//    //4. push column object to eSignFixture
//    eSignRGBColumn column;
//    column.setup(posX, posY, LEDNumber, direction,columnRectSize);
//    eSignRGBColumns.push_back(column);
//    //bAddColumn = false;
//
//}

//int eSignFixture::getEditMode()
//{
//    return editMode;
//}


//void eSignFixture::draw()
//{
//
//         for (int i =0; i < eSignRGBColumns.size(); i++)
//        {
//        ofPushMatrix();
//        ofPushStyle();
//        ofFill();
//        ofSetColor(eSignRGBColumns[i].getColor());
//        //ofSetRectMode(OF_RECTMODE_CENTER);
//        ofRect(eSignRGBColumns[i].columnRect);
//        ofNoFill();
//        ofSetColor(fixtureColor);
//        ofRect(eSignRGBColumns[i].columnRect);
//        ofDrawBitmapString(ofToString(i),eSignRGBColumns[i].columnRect.x,eSignRGBColumns[i].columnRect.y-5);
//        ofPopStyle();
//        ofPopMatrix();
//        }
//
//        ofPushMatrix();
//        ofPushStyle();
//        ofSetColor(fixtureColor);
//
//        ofBeginShape();
//         for (int i =0; i < eSignRGBColumns.size(); i++)
//        {
//
//
//        ofVertex(eSignRGBColumns[i].columnRect.x,eSignRGBColumns[i].columnRect.y);
//
//        }
//        ofEndShape();
//        ofPopStyle();
//        ofPopMatrix();
//
// }
