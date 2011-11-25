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
    NOEFFECT = 4,
    KINECTINPUT= 5,
    SOUNDINPUT= 6,
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
        void updateScene();
        void stopScene();

        void playEffect(sceneType scene, effectType effect);
        void updateEffect(effectType effect);
        void stopEffect(effectType effect);

        unsigned char * getPixels();
        ofRectangle getMovieSize();
        ofRectangle getEffectSize();

    private:
        sceneType currentScene;
        int currentMovie;
        effectType currentEffect;
        int currentEffect;
        ofRectangle movieRect;
        ofRectangle effectRect;

        int getMovieID(int type);



};

