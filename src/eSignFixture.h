#pragma once
#include "ofMain.h"
#include "ofEvents.h"
#include "eSignRGBColumn.h"



class eSignFixture
{
    public:
        eSignFixture();
        virtual ~eSignFixture();

        void mouseDragged(ofMouseEventArgs& args);
        void mousePressed(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);



        void setup(string address, ofColor c);

        vector<eSignRGBColumn> eSignRGBColumns;

        int addColumnGui();
        void addColumn(int LEDNumber, bool direction);


        void draw();
        //int gridRes;

        void setColorFromPixels(unsigned char * pixels);
        //void setGrid(ofVideoPlayer & video);
        int columnRectSize;
        float posX, posY;

    private:
        bool bGridChange;
        //unsigned char* pixels;
        ofColor fixtureColor;
        string UDPAddress;

        bool bAddColumn;

        int meanCnt;
        int meanR; int meanG;int meanB;
        int xStart;
        int yStart;
        int movWidth;
        int movHeight;
};
