#pragma once

#include "ofMain.h"
#include "movieToeSign.h"
#include "sceneManager.h"

#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345


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

        drawMode dMode;

        ofxOscReceiver	receiver;

};

