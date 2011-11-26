#pragma once

#include "ofMain.h"
#include "movieToeSign.h"
#include "sceneManager.h"
#include "hEvents.h"
// The event system used by hGui
// Can also be used to create new events and listeners

#include "hObject.h"
// Base object that contain virtual functions
// Objects that inherit from hObject can use its event listeners for free
#include "hGui_all.h"


class testApp : public ofBaseApp, public hObject{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


        //map image
        ofImage mapImg;


        bool bEdit;

        movieToeSign maze;
        sceneManager manager;
        sceneType scene;
        sceneControlType sceneControl;
        effectType effect;
        effectControlType effectControl;

};

