#pragma once
#include "ofMain.h"
#include "eSignFixture.h"


enum drawMode
{
    DRAW2D,
    DRAW3D
};


class movieToeSign
{
    public:
        movieToeSign();
        virtual ~movieToeSign();

        void mouseDragged(ofMouseEventArgs& args);
        void mousePressed(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);


        void addeSign(string UDPAddress, int numOfPorts);
        void addColumn(int fixtureNumber, int portNumber, float x, float y, int LEDNumber, bool direction);


        int getNumOfeSigns();
        int getEditMode();


        void guiHandler();
        void setColumnColorFromPixels(unsigned char * pixels);
        void draw(float x, float y, drawMode d);

        vector<eSignFixture> eSigns;

        int columnRectSize;



    private:
        int movWidth;
        int movHeight;

        int meanCnt;
        int meanR; int meanG;int meanB;
        int xStart;
        int yStart;
        float mouseX, mouseY;

        int editMode;
        ofRectangle movieRect;

};

