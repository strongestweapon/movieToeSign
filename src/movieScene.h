#pragma once
#include "ofMain.h"

class movieScene
{
    public:
        movieScene();
        virtual ~movieScene();


        void addMovie(string moviePath, int sceneName);
        int getSceneName();
        void setSceneName(int sceneName);

        void play(bool loop);
        void update();
        void stop();

        void draw();

        bool isMovieInScene();

        ofRectangle getMovieRect();

        ofVideoPlayer movie;

    private:
        int name;

        ofRectangle movieRect;
};
