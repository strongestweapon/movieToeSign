#include "eSignFixture.h"

eSignFixture::eSignFixture()
{
    UDPAddress="";
    fixtureColor = ofColor(0,0,0);

    rainbow[0] = ofColor(255,0,0);
    rainbow[1] = ofColor(255,50,0);
    rainbow[2] = ofColor(255,255,0);
    rainbow[3] = ofColor(0,255,0);
    rainbow[4] = ofColor(0,0,255);
    rainbow[5] = ofColor(0,0,127);
    rainbow[6] = ofColor(127,0,127);
    rainbow[7] = ofColor(255);


}

eSignFixture::~eSignFixture()
{
}

void eSignFixture::setup(string address,int numOfPorts)
{
    UDPAddress = address;
    e = new eSignUdp(UDPAddress,PORT, numOfPorts, CLUSTER_COUNT, DATA_SIZE);
    e->setDumpPacket(false);

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
    port.borderColor=rainbow[eSignPorts.size()];
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

void eSignFixture::update()
{
    for(int h = 0; h< eSignPorts.size(); h++)
    {
        for (int i =0; i < eSignPorts[h].eSignRGBColumns.size(); i++)
        {

       for (int k=0; k < eSignPorts[h].eSignRGBColumns[i].getNumOfLED() ; k++)
        {
            //////////////
            ofPushMatrix();
            ofPushStyle();
            ofSetColor(eSignPorts[h].eSignRGBColumns[i].getColor());
            ofRect(1024,400,100,100);
            ofPopStyle();
            ofPopMatrix();

            e->setPixel(h*(CLUSTER_COUNT)+(i*8)+k,
                eSignPorts[h].eSignRGBColumns[i].getColor().r,
                eSignPorts[h].eSignRGBColumns[i].getColor().g,
                eSignPorts[h].eSignRGBColumns[i].getColor().b
                );
        }
      }
    }


// 
//     for(int i = 0; i< eSignPorts.size(); i++)
//     {
//         cout << "1";
//         for (int j =0; j< eSignPorts[i].eSignRGBColumns.size(); j++)
//         {
//           // eSignRGBColumn column = eSignPorts[i].eSignRGBColumns[j];
//           cout << "2";
//            for (int k=0; k < column.getNumOfLED() ; k++)
//             {
//                 cout << "CLUSTER: ";
//                 cout << CLUSTER_COUNT << std::endl;
//                 cout << "RGBLedNumber: ";
//                 cout << column.RGBLedNumber << std::endl;
//                 int channel = i*(CLUSTER_COUNT)+(j*8)+k;
//                 cout << "CHANNEL: ";
//                 cout << channel << std::endl;
//                 cout << "COLOR R: ";
//                 cout << hex << (uint8_t)column.getColor().r << std::endl;
//                 cout << "COLOR G: ";
//                 cout << hex << (uint8_t)column.getColor().g << std::endl;
//                 cout << "COLOR B: ";
//                 cout << hex << (uint8_t)column.getColor().b << std::endl;
// 
//                 // ofPushMatrix();
//                 // ofPushStyle();
//                 // ofSetColor(column.getColor());
//                 // ofRect(1024,400,100,100);
//                 // ofPopStyle();
//                 // ofPopMatrix();
// 
//                 uint8_t red = column.getColor().r;
//                 cout << "COLOR uint8_t R: ";
//                 cout << hex << red << std::endl;
//                 uint8_t green = 255;
//                 uint8_t blue = 255;
// 
//                 e->setPixel(i*(CLUSTER_COUNT)+(j*8)+k,column.getColor().r,column.getColor().g,column.getColor().b);
//             }
//         }
//     }

    e->sendto();
}

int eSignFixture::getNumOfLED()
{
    fixtureLEDNumber = 0;
    for(int i = 0; i < eSignPorts.size(); i++)
    {
        fixtureLEDNumber = fixtureLEDNumber + eSignPorts[i].getNumOfLED();
    }
    return fixtureLEDNumber;
}
