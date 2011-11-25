#pragma once
#include "ofMain.h"

class eSignRGB
{
    public:
        eSignRGB();
        virtual ~eSignRGB();

        void setColor(ofColor c);
        ofColor getColor();


        float posZ;
        int posNetwork;


    private:
        ofColor LEDColor;

};


