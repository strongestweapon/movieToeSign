#pragma once
#include "ofMain.h"

class RGBfixture
{
    public:
        RGBfixture();
        virtual ~RGBfixture();

        //adding mouse events to a class http://www.slideshare.net/roxlu/openframeworks-007-events
        //void mousePressed(ofMouseEventArgs& args);

        void setRGB(unsigned char R, unsigned char G, unsigned char B);

        //void draw(float x, float y, float width, float height);


    protected:
    private:
        ofColor c;
        ofRectangle fixtureRect;

        bool bFixtureSet;
};


