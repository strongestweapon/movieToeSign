#include "testApp.h"
//#include "hGui_all.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(0);
    mapImg.loadImage("map/map.png");
    bEdit = false;

    //scene manager setup
    manager.addScene("movies/red.mov",INTRO);
    manager.addScene("movies/blue.mov",MOVIEA);
    manager.addScene("movies/yellow.mov",MOVIEB);
    manager.addScene("movies/green.mov",OUTRO);
//    manager.addEffect("movies/kinect.mov",KINECTINPUT);
//    manager.addEffect("movies/sound.mov",SOUNDINPUT);

    //initialize scene & effect
    scene = INTRO;
    sceneControl = SCENEPLAY;
    effect = NOEFFECT;
    effectControl = EFFECTOFF;

    ofRectangle movieRect = manager.getMovieSize();

    //initialize the maze

    maze.guiSetup();
    maze.setMovieRect(movieRect);
    maze.addeSign("192.168.1.11",8);
    maze.addeSign("192.168.1.12",8);
    maze.addeSign("192.168.1.13",8);
    maze.addeSign("192.168.1.14",8);
    maze.addeSign("192.168.1.15",8);
    maze.addeSign("192.168.1.16",8);
    maze.addeSign("192.168.1.17",8);
    maze.addeSign("192.168.1.18",8);
    maze.addeSign("192.168.1.19",8);

    maze.setColumnRectSize(10); //after we assign eSigns and Ports, we change the columnRect size recursively
}

//--------------------------------------------------------------
void testApp::update(){
    //get add or edit mode

    maze.getEditMode();

    manager.update(scene,sceneControl,effect,effectControl);

}

//--------------------------------------------------------------
void testApp::draw(){

    ofPushStyle();
    ofSetColor(255);
    manager.drawScene(0,0);
    ofPopStyle();

    unsigned char * pixels = manager.getScenePixels();
    maze.setColumnColorFromPixels(pixels);

    ofPushMatrix();
    maze.draw(0,0,DRAW2D);
    ofPopMatrix();
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
