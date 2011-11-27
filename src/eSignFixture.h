#pragma once
#include "ofMain.h"
#include "eSignPort.h"
#include "eSignUdp.h"

class eSignFixture
{
    public:
        eSignFixture();
        virtual ~eSignFixture();

        vector<eSignPort> eSignPorts;
        ofColor fixtureColor;

        void setup(string address, int numOfPorts);
        void addPort();
        void addColumn(int portNumber, float x, float y, int LEDNumber, bool direction);
        void setColor(ofColor c);
        ofColor getColor();

        void update();

    private:
        eSignUdp* e;
        string UDPAddress;


};
