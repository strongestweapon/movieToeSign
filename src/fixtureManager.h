#pragma once
#include "ofMain.h"
#include "RGBfixture.h"

class fixtureManager
{
    public:
        fixtureManager();
        virtual ~fixtureManager();

        vector<RGBfixture> RGBfixtures;

        int gridRes;

        void setFromVideo(ofVideoPlayer & video);
        void setGrid(ofVideoPlayer & video);


    private:
        bool bGridChange;
        unsigned char* pixels;
};
