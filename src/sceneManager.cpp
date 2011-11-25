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

}




//	OF_LOOP_NONE=0x01,
//	OF_LOOP_PALINDROME=0x02,
//	OF_LOOP_NORMAL=0x03
