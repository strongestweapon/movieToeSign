#pragma once
#include "ofMain.h"

enum sceneType
{
    INTRO,
    MOVIEA,
    MOVIEB,
    OUTRO
};

enum subSceneType
{
    STARTED,
    PLAYING,
    ENDED
};

enum effectType
{
    NOEFFECT,
    KINECTINPUT,
    SOUNDINPUT,
};

typedef struct metaMov
{
    public:
        int movieID;
        int type;
} movieInfo;

class sceneManager
{
    public:
        sceneManager();
        virtual ~sceneManager();

        vector<ofVideoPlayer> movies;
        vector<movieInfo> movieInfos;

        void loadMovieToScene(string moviePath, sceneType scene);
        void loadMovieToEffect(string moviePath, effectType effect);

        void playScene(sceneType scene, bool loop);
        void stopScene();
        void updateScene();

        void palyEffect(sceneType scene, effectType effect);
        void stopEffect(effectType effect);

        unsigned char * getPixels();
        ofRectangle getMovieSize();
        ofRectangle getEffectSize();

    private:
        ofRectangle movieRect;
        ofRectangle effectRect;


};

