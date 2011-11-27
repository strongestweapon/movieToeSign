#include "eSignFixture.h"

eSignFixture::eSignFixture()
{
    UDPAddress="";
    fixtureColor = ofColor(0,0,0);

}

eSignFixture::~eSignFixture()
{
}

void eSignFixture::setup(string address,int numOfPorts)
{
    UDPAddress = address;
    e = new eSignUdp(UDPAddress,PORT, numOfPorts, CLUSTER_COUNT, DATA_SIZE);
    e->setDumpPacket(true);

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
    eSignPorts.push_back(port);

}


void eSignFixture::setColor(ofColor c)
{

    for(int i =0; i< eSignPorts.size(); i++)
    {
        eSignPorts[i].setColor(c);
    }
}



ofColor eSignFixture::getColor()
{
    return fixtureColor;
}

void eSignFixture::update()
{
    for(int i = 0; i< eSignPorts.size(); i++)
    {
        for (int j =0; j< eSignPorts[j].eSignRGBColumns.size(); j++)
        {
            eSignRGBColumn column = eSignPorts[j].eSignRGBColumns[j];
            for (int k=0; k < column.RGBLedNumber ; k++)
            {
                e->setPixel(i*(CLUSTER_COUNT)+(j*column.RGBLedNumber)+k,
                            column.getColor().r,
                            column.getColor().g,
                            column.getColor().b
                            );
//                cout << hex << column.getColor().r << std::endl;
//                cout << hex << column.getColor().g << std::endl;
//                cout << hex << column.getColor().b << std::endl;
            }
        }
    }

    e->sendto();
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
