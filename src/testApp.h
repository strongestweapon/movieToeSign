#pragma once

#include "ofMain.h"
#include "eSignFixture.h"
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
		void exit();
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

		ofVideoPlayer 		fingerMovie;
		bool                frameByframe;

		int movWidth;
		int movHeight;

        int gridRes;

        eSignFixture eSign1;


        ofTrueTypeFont * font;
        std::string myString;
        void setText(std::string text);
        void clearText(void);
        void setLabel(std::string label);
        void scene1(void);
        void scene2(void);
        void scene3(void);
        void scene4(void);

        //map image
        ofImage mapImg;
        ofImage tempImg;


        bool bEdit;


};

