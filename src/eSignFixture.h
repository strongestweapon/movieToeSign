#pragma once
#include "ofMain.h"
#include "eSignPort.h"


class eSignFixture
{
    public:
        eSignFixture();
        virtual ~eSignFixture();

        void setup(string address, int numOfPorts);
        void addPort();
        void setColor(ofColor c);
        ofColor getColor();

        vector<eSignPort> eSignPorts;
        ofColor fixtureColor;


    private:

        string UDPAddress;


};
