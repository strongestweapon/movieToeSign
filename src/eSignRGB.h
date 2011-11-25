#pragma once
#include "ofMain.h"

class eSignRGB
{
    public:
        eSignRGB();
        virtual ~eSignRGB();

        //adding mouse events to a class http://www.slideshare.net/roxlu/openframeworks-007-events
        //void mousePressed(ofMouseEventArgs& args);

        void setColor(unsigned char R, unsigned char G, unsigned char B);
        ofColor getColorAtPosZ(float posZ);
        ofColor getColorForNet(int posNetwork);
        //void draw(float x, float y, float width, float height);
         float posZ;
         int posNetwork;

    protected:
    private:
        ofColor c;
        //ofRectangle fixtureRect;


        bool bFixtureSet;
};


