#include "RGBfixture.h"

RGBfixture::RGBfixture()
{
    //ofRegisterMouseEvents(this);
    bFixtureSet = false;
    c.r=0;
    c.g=0;
    c.b=0;
}

RGBfixture::~RGBfixture()
{
    //dtor
}




void RGBfixture::setRGB(unsigned char R, unsigned char G, unsigned char B)
{
    c.r = R;
    c.g = G;
    c.b = B;
}


//void RGBfixture::draw(float x, float y, float width, float height)
//{
//    ofPushMatrix();
//    ofPushStyle();
//    fixtureRect = ofRectangle(x,y,width,height);
//    ofSetColor((unsigned char)c.r,(unsigned char)c.g,(unsigned char)c.b);
//    ofFill();
//    ofRect(fixtureRect);
//    ofNoFill();
//    ofSetColor(0);
//    ofRect(fixtureRect);
//    ofPopStyle();
//    ofPopMatrix();
//}

//void RGBfixture::setFixutre()
//{
//    //if mouse click coordinates are inside of fixture rect
//    //toggle the bFixtureSet flag
//
//
//
//
//}
