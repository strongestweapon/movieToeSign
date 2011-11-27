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


        void setup(float x, float y, int LEDNumber, bool direction, float rectSize);
        void setColor(ofColor c);
        ofColor getColor();
        int portNumber;

        ofColor getColorAtPosZ(float z);
        ofColor getColorForNet(int posN);

        int RGBLedNumber;

    protected:
    private:
        float posX, posY;
        bool direction;
        ofColor columnColor;


};


