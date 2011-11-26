#include "sceneManager.h"

sceneManager::sceneManager()
{
    subScene = ENDED;
    subEffect = ENDED;
}

sceneManager::~sceneManager()
{
    //dtor
}

void sceneManager::addScene(string moviePath, sceneType scene)
{
    movieScene sceneMov;
    sceneMov.addMovie(moviePath, scene);
    movieRect = sceneMov.getMovieRect();
    scene_map[scene] = scenes.size();
    scenes.push_back(sceneMov);
}

void sceneManager::addEffect(string moviePath, effectType effect)
{
    movieScene effectMov;
    effectMov.addMovie(moviePath, effect);
    effectRect = effectMov.getMovieRect();
    effect_map[effect] = effects.size();
    effects.push_back(effectMov);
}

void sceneManager::playScene(sceneType scene, bool loop)
{
    int id = scene_map[scene];
    scenes[id].play(loop);
}

void sceneManager::updateScene(sceneType scene)
{
    int id = scene_map[scene];
    scenes[id].update();
}


void sceneManager::stopScene(sceneType scene)
{
    int id = scene_map[scene];
    scenes[id].stop();
}

void sceneManager::playEffect(effectType effect, bool loop)
{
    int id = effect_map[effect];
    effects[id].play(loop);
}

void sceneManager::updateEffect(effectType effect)
{
    int id = effect_map[effect];
    effects[id].update();
}

void sceneManager::stopEffect(effectType effect)
{
    int id = effect_map[effect];
    effects[id].stop();
}

void sceneManager::update(sceneType scene, sceneControlType sceneControl, effectType effect, effectControlType effectControl)
{
    //set current scene & control
    currentScene = scene;
    currentSceneControl = sceneControl;
    //set current effect & control
    currentEffect = effect;
    currentEffectControl = effectControl;

    //scence play manager
    if(currentSceneControl == SCENEPLAY && subScene == ENDED)
    {
        subScene = PLAYING;
        playScene(currentScene, true);
    }

    if(currentSceneControl == SCENEONCE && subScene == ENDED)
    {
        subScene = PLAYING;
        playScene(currentScene, false);
    }

    if(currentSceneControl == SCENESTOP && subScene == PLAYING)
    {
        subScene = ENDED;
        stopScene(currentScene);
    }

    if(currentSceneControl == SCENEPLAY || currentSceneControl == SCENEONCE )
    {
        updateScene(currentScene);
    }


    //effect play manager
    if(currentEffectControl == EFFECTON && subEffect == ENDED)
    {
        subEffect = PLAYING;
        playEffect(currentEffect, true);
    }


    if(currentEffectControl == EFFECTOFF && subEffect == PLAYING)
    {
        subEffect = ENDED;
        stopEffect(currentEffect);
    }

    if(currentEffectControl == EFFECTON)
    {
        updateEffect(currentEffect);
    }
}

void sceneManager::drawScene(float x, float y)
{
    int id = scene_map[currentScene];
    movieRect.x = x;
    movieRect.y= y;

    ofPushMatrix();
    ofTranslate(x,y,0);
    scenes[id].draw();
    ofPopMatrix();

}

unsigned char* sceneManager::getScenePixels()
{
    int id = scene_map[currentScene];
    return scenes[id].movie.getPixels();
}

unsigned char* sceneManager::getEffectPixels()
{
    int id = effect_map[currentEffect];
    return effects[id].movie.getPixels();
}

ofRectangle sceneManager::getMovieSize()
{
    return movieRect;
}

ofRectangle sceneManager::getEffectSize()
{
    return effectRect;
}
