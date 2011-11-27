#pragma once
#include "ofMain.h"
#include "eSignRGBColumn.h"

class eSignPort
{
    public:
        eSignPort();
        virtual ~eSignPort();

        void addColumn(float x, float y, int LEDNumber, bool direction);
        void setColor(ofColor c);
        void setColumnRectSize(int size);

        int getNumOfLED();

        vector<eSignRGBColumn> eSignRGBColumns;
        int columnRectSize;
        ofColor borderColor;
    private:
        int portLEDNumber;

};


