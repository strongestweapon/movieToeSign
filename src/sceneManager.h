#pragma once
#include "ofMain.h"
#include "movieScene.h"

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

enum sceneControlType
{
    SCENEPLAY,
    SCENESTOP,
    SCENEONCE
};

enum effectType
{
    NOEFFECT,
    KINECTINPUT,
    SOUNDINPUT
};

enum effectControlType
{
    EFFECTON,
    EFFECTOFF
};



class sceneManager
{
    public:
        sceneManager();
        virtual ~sceneManager();

        map<sceneType, int> scene_map;
        map<effectType, int> effect_map;

        vector<movieScene> scenes;
        vector<movieScene> effects;

        void addScene(string moviePath, sceneType scene);
        void addEffect(string moviePath, effectType effect);

        void update(sceneType scene, sceneControlType sceneControl, effectType effect, effectControlType effectControl); //set current scene and control

        void drawScene(float x, float y);
        //void drawEffect(float x, float y, effectType effect);

        unsigned char * getScenePixels();
        unsigned char * getEffectPixels();
        ofRectangle getMovieSize();
        ofRectangle getEffectSize();

    private:
        void playScene(sceneType scene, bool loop);
        void updateScene(sceneType scene);
        void stopScene(sceneType scene);

        void playEffect(effectType effect, bool loop);
        void updateEffect(effectType effect);
        void stopEffect(effectType effect);

        int subScene;
        int subEffect;

        sceneType currentScene;
        sceneControlType currentSceneControl;

        effectType currentEffect;
        effectControlType currentEffectControl;

        ofRectangle movieRect;
        ofRectangle effectRect;

};

