#pragma once
#include "ofMain.h"
#include "eSignRGB.h"

class eSignRGBColumn
{
    public:
        eSignRGBColumn();
        virtual ~eSignRGBColumn();

        vector<eSignRGB> eSignRGBs;
        ofRectangle columnRect;


        void setup(float x, float y, int LEDNumber, bool direction, int rectSize);
        void setColor(ofColor c);
        ofColor getColor();
        int getNumOfLED();

        int portNumber;

        ofColor getColorAtPosZ(float z);
        ofColor getColorForNet(int posN);

        int RGBLedNumber;
        float posX, posY;
        bool direction;

    protected:
    private:

        ofColor columnColor;


};


