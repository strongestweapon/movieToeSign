#include "movieScene.h"

movieScene::movieScene()
{
    //ctor
}

movieScene::~movieScene()
{
    //dtor
}

void movieScene::addMovie(string moviePath, int sceneName)
{
    if(!moviePath.empty())
    {
        movie.loadMovie(moviePath);
        movieRect = ofRectangle(0,0,movie.width,movie.height);
    }
    name = sceneName;
}


int movieScene::getSceneName()
{
    return name;
}

void movieScene::setSceneName(int sceneName)
{
    name = sceneName;
}

ofRectangle movieScene::getMovieRect()
{
     return movieRect;
}


void movieScene::play(bool loop)
{
    if(loop)
    {
        movie.setPosition(0);
        movie.play();
    }
    else
    {
        movie.setLoopState(OF_LOOP_NONE);
        movie.setPosition(0);
        movie.play();
    }
}

void movieScene::update()
{

    movie.idleMovie();
}

void movieScene::stop()
{
    movie.stop();
}

bool movieScene::isMovieInScene()
{
    if(movie.isLoaded())
        return true;
    else
        return false;
}
