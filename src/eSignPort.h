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
        int getNumOfeSignRGB();

        vector<eSignRGBColumn> eSignRGBColumns;
        int columnRectSize;

    private:
        int portLEDNumber;

};


