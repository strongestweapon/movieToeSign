#pragma once
#include "ofMain.h"

class eSignRGB
{
    public:
        eSignRGB();
        virtual ~eSignRGB();

        void setColor(ofColor c);
        ofColor getColor();

        void setPosition(int x,int y,int z);

        int getX();
        int getY();
        int getZ();

        void setPosNetwork(int _posNetwork);

    private:
        ofColor LEDColor;

        int posX;
        int posY;
        int posZ;
        int posNetwork;

};


