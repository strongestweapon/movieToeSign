#pragma once
#include "ofMain.h"
#include "eSignFixture.h"
#include "hEvents.h"
#include "hObject.h"
#include "hGui_all.h"

enum drawMode
{
    DRAW2D,
    DRAW3D
};

enum editModeType
{
    ADD,
    EDIT,
    DONE
};

class movieToeSign: public hObject
{
    public:
        movieToeSign();
        virtual ~movieToeSign();

        void mouseDragged(ofMouseEventArgs& args);
        void mousePressed(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);

        void setMovieRect(ofRectangle rect);
        void setColumnRectSize(int size);
        void addeSign(string UDPAddress, int numOfPorts);
        void addColumn(int fixtureNumber, int portNumber, float x, float y, int LEDNumber, bool direction);


        int getNumOfeSigns();
        int getNumOfLED();
        int getNumOfLEDinPort(int fixtureNumber, int portNumber);
        editModeType getEditMode();


        void guiHandler();
        void setColumnColorFromPixels(unsigned char * pixels);
        void draw(float x, float y, drawMode d);

        vector<eSignFixture> eSigns;

        int columnRectSize;

        void guiSetup();

    private:
        int movWidth;
        int movHeight;

        int meanCnt;
        float meanR; float meanG;float meanB;
        int xStart;
        int yStart;
        float mouseX, mouseY;
        float saveX,saveY;

        editModeType editMode;
        bool mouseOnMovie;

        ofRectangle movieRect;
        int movieLEDNumber;
        int portLEDNumber;


        //gui members

        void exit();
        void start(void);
        void stop(void);
        void clear(void);

        void setValue(double val);
        void setValueToItem(double val, int index);
        void setXY(double x, double y);

        void selectItem(int item);
        void itemSetSelected(int item, bool flag);

        void setLabel(std::string label);

        void setText(std::string text);
        void addText(std::string text);
        void clearText(void);

        void openItem(int index);
        void answerDialog(int buttonID);

        // Custom listener:
        void setColors(hEventArgs& args);

        // GUI color customization example:
        void setDarkColors(void);
        void setLedColor(int* red, int* green,int* blue);
        // Variables used by the widgets (linked to them) :
        bool drawFlag;

        int red, green, blue;

        float xPct, yPct;

        int curTime;

        // Other objects:
        hGui * gui;
        ofTrueTypeFont * font;
        std::string myString;

        hSlider*  slider1;
        hSlider*  slider2;
        hSlider*  slider3;

};

