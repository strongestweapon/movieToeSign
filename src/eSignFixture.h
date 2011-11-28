#pragma once
#include "ofMain.h"
#include "eSignPort.h"

class eSignFixture
{
    public:
        eSignFixture();
        virtual ~eSignFixture();

        vector<eSignPort> eSignPorts;
        ofColor fixtureColor;
        map<int, ofColor> rainbow;
        void setup(string address, int numOfPorts);
        void addPort();
        void addColumn(int portNumber, float x, float y, int LEDNumber, bool direction);
        void setColor(ofColor c);
        void setColumnRectSize(int size);

        int getNumOfLED();
        ofColor getColor();




    private:
        int fixtureLEDNumber;
        string UDPAddress;


};
