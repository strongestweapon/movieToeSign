#include "testApp.h"
//#include "hGui_all.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(0);
    mapImg.loadImage("map/map.png");
    bEdit = false;

    //scene manager setup
    manager.addScene("movies/color.mov",INTRO);
    //manager.addScene("movies/red.mov",INTRO);
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

    //maze setup
    maze.guiSetup();
    maze.setMovieRect(movieRect);
    maze.addeSign("192.168.0.100",8);
    maze.addeSign("192.168.0.101",8);
    maze.addeSign("192.168.0.102",8);
    maze.addeSign("192.168.0.103",8);
    maze.addeSign("192.168.0.104",8);
    maze.addeSign("192.168.0.105",8);
    maze.addeSign("192.168.0.106",8);
    maze.addeSign("192.168.0.107",8);
    maze.addeSign("192.168.0.108",8);
    maze.setColumnRectSize(10); //after we assign eSigns and Ports, we change the columnRect size recursively
    dMode = DRAW2D;

    receiver.setup( PORT );
}

//--------------------------------------------------------------
void testApp::update(){

	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );

		// check for mouse moved message
		if ( m.getAddress() == "/scene" )
		{
			// both the arguments are int32's
			scene = (sceneType)m.getArgAsInt32( 0 );
			sceneControl = (sceneControlType)m.getArgAsInt32( 1 );
		}
		else
		{
			return;
		}

	}

    manager.update(scene,sceneControl,effect,effectControl);

}

//--------------------------------------------------------------
void testApp::draw(){

    if(dMode == DRAW2D){
    ofPushStyle();
    ofSetColor(255);
    manager.drawScene(0,0);
    ofPopStyle();
    }

    unsigned char * pixels = manager.getScenePixels();
    maze.setColumnColorFromPixels(pixels);

    ofPushMatrix();

    maze.draw(0,0,dMode);

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
        case ' ':
        dMode = DRAW3D;
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
        case ' ':
        dMode = DRAW2D;
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
