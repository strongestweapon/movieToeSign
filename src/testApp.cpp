#include "testApp.h"
//#include "hGui_all.h"

//--------------------------------------------------------------
void testApp::setup(){
    /*gui start*/
    ofSetWindowTitle("ofxhGuiExample1 - openFrameworks 7");
    hGui * gui = hGui::getInstance();
    gui->setup("fonts/DIN.otf", 9);


    hPanel * mainPanel =
	gui->addPanel("mainPanel", NULL, HGUI_ABSOLUTE_POSITION, ofGetWidth()-300-20, 40, 300, 400, true);
    mainPanel->setVisibleBackground(true);



    gui->setRootWidget(mainPanel);
    gui->addListeners();

   hButton* button1 =
	gui->addButton("button1", mainPanel, HGUI_TOP_LEFT, gui->margin3, gui->margin3, 100, "Scene #1");

	hButton* button2 =
	gui->addButton("button2", mainPanel, HGUI_NEXT_ROW, gui->margin3, gui->margin3, 100, "Scene #2");

	hButton* button3 =
	gui->addButton("button3", mainPanel, HGUI_NEXT_ROW, gui->margin3, gui->margin3, 100, "Scene #3");

	hButton* button4 =
	gui->addButton("button4", mainPanel, HGUI_NEXT_ROW, gui->margin3, gui->margin3, 100, "Scene #4");

	// Set the message that the buttons will send when pressed
	// The form of the message is "object.method"
	button1->setMessage("testApp.scene1");
	button2->setMessage("testApp.scene2");
	button3->setMessage("testApp.scene3");
	button4->setMessage("testApp.scene4");





    gui->setFixedFont("fonts/lmmonolt10-bold.otf", 10, 0);

    myString = "";

    hEvents * events = hEvents::getInstance();
	events->setup();
	events->addObject("testApp", this);




    //create tab
    int mainTabBoxWidth = mainPanel->getWidth();
    //hTabBox *  mainTabBox =
    mainTabBox =
		gui->addTabBox("mainTabBox", NULL, HGUI_ABSOLUTE_POSITION, ofGetWidth()-300-20, 20, mainTabBoxWidth);
    mainTabBox->addItems(3);
    mainTabBox->setItemLabel(1, "Play");
	mainTabBox->setItemLabel(2, "Edit");
	mainTabBox->setItemLabel(3, "Test");
	mainTabBox->setItemPanel(1, mainPanel); // Let our main panel to be the fist tab
	mainTabBox->selectItem(1);			// and select it


	gui->setRootWidget(mainTabBox);

     hPanel * mainPanel2 =
		gui->addPanel(
		"mainPanel2", NULL, HGUI_ABSOLUTE_POSITION, ofGetWidth()-300-20, 40, mainPanel->getWidth(), mainPanel->getHeight(), true);
	mainPanel2->setVisibleBackground(true);
	mainTabBox->setItemPanel(2, mainPanel2);


    //number of LED
    hTextArea * textLEDNumber = gui->addTextArea("LEDNumber", mainPanel2, HGUI_TOP_LEFT, gui->margin2, gui->margin2, 170, 50);

	textLEDNumber->setText("8", false);
    textLEDNumber->addTools(60, -1, "OK", "RESET");
	textLEDNumber->setMessage("testApp.setText");
	textLEDNumber->setMessage2("testApp.clearText");


    hPanel * mainPanel3 =
		gui->addPanel(
		"mainPanel3", NULL, HGUI_ABSOLUTE_POSITION, ofGetWidth()-300-20, 40, mainPanel->getWidth(), mainPanel->getHeight(), true);
	mainPanel3->setVisibleBackground(true);
	mainTabBox->setItemPanel(3, mainPanel3);






	ofBackground(0);

	frameByframe = false;

	fingerMovie.loadMovie("movies/fingers.mov");

	movWidth = fingerMovie.getWidth();
	movHeight = fingerMovie.getHeight();


	fingerMovie.play();

    gridRes = 20;
    ofColor c = ofColor(255,0,0);




    //eSign1.setup("168.33.44.1",c);

    mapImg.loadImage("map/map.png");
    bEdit = false;
}

void testApp::exit()
{
    hGui * gui = hGui::getInstance();

	gui->saveSettings("settings.xml"); // You can of course call that elsewhere


}

void testApp::scene1(void){
	myString = "scene1";
}

void testApp::scene2(void){
	myString = "scene2";
}

void testApp::scene3(void){
	myString = "scene3";
}

void testApp::scene4(void){
	myString = "scene4";
}

void testApp::setLabel(std::string label)
{
	myString = label;
}


void testApp::setText(std::string text)
{
	myString = text; // Not very clever processing...
	// it's just a test
}

void testApp::clearText(void)
{
	myString.clear();
}


//--------------------------------------------------------------
void testApp::update(){


    fingerMovie.idleMovie();




//    if (0 == eSign1.addColumnGui() || 2 ==eSign1.addColumnGui())
//    {
//        cout << eSign1.posX << std::endl;
//    }

}

//--------------------------------------------------------------
void testApp::draw(){

    if(bEdit){
        ofPushStyle();
        ofSetColor(255);
        mapImg.draw(20,20);
        ofPopStyle();
    }
	ofSetHexColor(0xFFFFFF);
    fingerMovie.draw(0,0);
    ofSetHexColor(0x000000);
    unsigned char * pixels = fingerMovie.getPixels();
    // let's move through the "RGB" char array
    // using the red pixel to control the size of a circle.

//    int aa;
//    aa = pixels.length();
//    cout << aa << std::endl;




//
//    int meanCnt;
//    int meanR, meanG, meanB;
//    int gridWidth = gridRes;
//    int gridHeight = gridRes;
//    int meanPixCnt=0;
//
//    //mean value mosaic ref: http://naver.gogil.kr/100085780565
//
//    for (int i = 0; i < movWidth; i+=gridRes){
//        for (int j = 0; j < movHeight; j+=gridRes){
//
//            meanCnt =0;
//            meanR=0;meanG=0;meanB=0;
//
//            if((i+gridRes) > movWidth) gridWidth = movWidth%gridRes;
//            else gridWidth=gridRes;
//
//
//            if((j+gridRes) > movHeight) gridHeight = movHeight%gridRes;
//            else gridHeight=gridRes;
//
//            for( int m = 0; m< gridWidth ; m++){
//                for(int n = 0; n<gridHeight ; n++){
//
//                meanR += pixels[(i+m + (j+n)*movWidth)*3];
//                meanG += pixels[(i+m + (j+n)*movWidth)*3 +1];
//                meanB += pixels[(i+m + (j+n)*movWidth)*3 +2];
//
//
//                meanCnt++;
//                }
//            }
//
//            meanR/=meanCnt;
//            meanG/=meanCnt;
//            meanB/=meanCnt;
//
//            ofPushMatrix();
//            ofTranslate(0,0,0);
//            //ofScale(1.5,1.5,1);
//            ofPushStyle();
//            ofRectangle gridRect;
//            //ofSetRectMode(OF_RECTMODE_CENTER);
//            gridRect = ofRectangle(i,j,gridWidth,gridHeight);
//            ofSetColor((unsigned char)meanR,(unsigned char)meanG,(unsigned char)meanB);
//            ofFill();
//            ofRect(gridRect);
//            ofNoFill();
//            ofSetColor(0);
//            ofRect(gridRect);
//            ofPopStyle();
//            ofPopMatrix();
//
//
//
//
//            meanPixCnt++;
//        }
//    }



    ofSetHexColor(0x000000);
	ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetHexColor(0x000000);

    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);
    //ofDrawBitmapString("how many tile pixels?: " + ofToString(meanPixCnt),400,320);

    if(fingerMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }




}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key){
        case 'f':
            frameByframe=!frameByframe;
            fingerMovie.setPaused(frameByframe);
        break;
        case OF_KEY_LEFT:
            fingerMovie.previousFrame();
        break;
        case OF_KEY_RIGHT:
            fingerMovie.nextFrame();
        break;
        case '0':
            fingerMovie.firstFrame();
        break;

        case OF_KEY_UP:
            gridRes++;
            if(gridRes > 32) gridRes = 32;
        break;

        case OF_KEY_DOWN:
            gridRes--;
            if(gridRes < 2) gridRes = 2;
        break;

    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        fingerMovie.setPosition(pct);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(true);
	}



//cout << "main:" << std::endl;




}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(false);
	}
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
