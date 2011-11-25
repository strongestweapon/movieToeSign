#pragma once
#include "ofMain.h"
#include "eSignRGB.h"

class eSignRGBColumn
{
    public:
        eSignRGBColumn();
        virtual ~eSignRGBColumn();

        void mouseDragged(ofMouseEventArgs& args);
        void mousePressed(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);



        vector<eSignRGB> eSignRGBs;
        ofRectangle columnRect;


        void setup(float x, float y, int LEDNumber, bool direction, float rectSize);
        void setColor(ofColor c);
        ofColor getColor();
        int portNumber;

    protected:
    private:
        float posX, posY;
        int RGBLedNumber;
        bool direction;
        ofColor columnColor;


};


