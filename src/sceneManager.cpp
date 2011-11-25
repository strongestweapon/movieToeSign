#include "sceneManager.h"

sceneManager::sceneManager()
{
    //ctor
}

sceneManager::~sceneManager()
{
    //dtor
}

void sceneManager::loadMovieToScene(string moviePath, sceneType scene)
{
    ofVideoPlayer movie;
    movie.loadMovie(moviePath);
    movieRect = ofRectangle(0,0,movie.width,movie.height);
    movies.push_back(movie);

    movieInfo info;
    info.movieID = movies.size()-1;
    info.type = scene;
    movieInfos.push_back(info);

}

void sceneManager::loadMovieToEffect(string moviePath, effectType effect)
{
    ofVideoPlayer movie;
    movie.loadMovie(moviePath);
    effectRect = ofRectangle(0,0,movie.width,movie.height);
    movies.push_back(movie);

    movieInfo info;
    info.movieID = movies.size()-1;
    info.type = effect;
    movieInfos.push_back(info);
}

int sceneManager::getMovieID(int type)
{
    for(int i = 0; i < movies.size() ; i++)
    {
        if(movieInfos[i].type == type)
        return i;
    }

    return -1;

}

void sceneManager::playScene(sceneType scene, bool loop)
{
    currentScene = scene;
    currentMovie = getMovieID(scene);
    if (currentMovie >= 0)
    {
        if(loop) movies[currentMovie].setLoopState(OF_LOOP_NORMAL);
        else movies[currentMovie].setLoopState(OF_LOOP_NONE);
        movies[currentMovie].play();
    }
}

void sceneManager::updateScene()
{
    movies[currentMovie].idleMovie();
}

void sceneManager::stopScene()
{
    movies[currentMovie].stop();
    movies[currentMovie].setPosition(0);
}

//	OF_LOOP_NONE=0x01,
//	OF_LOOP_PALINDROME=0x02,
//	OF_LOOP_NORMAL=0x03
