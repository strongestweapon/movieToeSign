#include "testApp.h"
//#include "hGui_all.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(0);
    mapImg.loadImage("map/map.png");
    bEdit = false;

    manager.addScene("movies/red.mov",INTRO);
    manager.addScene("movies/blue.mov",MOVIEA);
    manager.addScene("movies/yellow.mov",MOVIEB);
    manager.addScene("movies/green.mov",OUTRO);
    manager.addEffect("movies/kinect.mov",KINECTINPUT);
    manager.addEffect("movies/sound.mov",SOUNDINPUT);

    //initialize scene & effect
    scene = INTRO;
    sceneControl = SCENEPLAY;
    effect = NOEFFECT;
    effectControl = EFFECTOFF;


    //initialize the maze

    maze.setMovieRect(manager.getMovieSize());
    maze.addeSign("192.168.0.100",8);
    maze.addeSign("192.168.0.101",8);
    maze.addeSign("192.168.0.102",8);
    maze.addeSign("192.168.0.103",8);
    maze.addeSign("192.168.0.104",8);
    maze.addeSign("192.168.0.105",8);
    maze.addeSign("192.168.0.106",8);
    maze.addeSign("192.168.0.107",8);
    maze.addeSign("192.168.0.108",8);

}



//--------------------------------------------------------------
void testApp::update(){
    maze.getEditMode();
    manager.update(scene,sceneControl,effect,effectControl);

}

//--------------------------------------------------------------
void testApp::draw(){

    if(bEdit){
        ofPushStyle();
        ofSetColor(255);
        mapImg.draw(20,20);
        ofPopStyle();
    }

    ofPushStyle();
    ofSetColor(255);
    manager.drawScene(0,0);
    ofPopStyle();

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key)
    {
        case '1':
        scene = INTRO;
        sceneControl = SCENEPLAY;
        break;

        case '2':
        scene = MOVIEA;
        sceneControl = SCENEPLAY;
        break;

        case '3':
        scene = MOVIEB;
        sceneControl = SCENEPLAY;
        break;

        case '4':
        scene = OUTRO;
        sceneControl = SCENEPLAY;
        break;

    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch(key)
    {
        case '1':
        scene = INTRO;
        sceneControl = SCENESTOP;
        break;

        case '2':
        scene = MOVIEA;
        sceneControl = SCENESTOP;
        break;

        case '3':
        scene = MOVIEB;
        sceneControl = SCENESTOP;
        break;

        case '4':
        scene = OUTRO;
        sceneControl = SCENESTOP;
        break;

    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
