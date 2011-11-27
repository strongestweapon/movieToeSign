#include "movieToeSign.h"

movieToeSign::movieToeSign()
{
    ofRegisterMouseEvents(this);
    editMode = DONE;
    columnRectSize = 20;

}

movieToeSign::~movieToeSign()
{
    exit();
}

void movieToeSign::mousePressed(ofMouseEventArgs& args)
{
    mouseX = args.x;
    mouseY = args.y;

    if (mouseX <  movieRect.width - columnRectSize && mouseY <  movieRect.height - columnRectSize )
    {
        mouseOnMovie = true;
        guiHandler();
    }
    else
    {
        mouseOnMovie = false;

    }
    cout << "movieRect:" <<' ';
    cout << movieRect.width <<'\t';
    cout << movieRect.height << endl;

    cout << "columnRectSize:" <<' ';
    cout << columnRectSize << endl;

    cout << "mouse:" <<' ';
    cout << mouseX <<'\t';
    cout << mouseY <<endl;
    cout << editMode <<endl;

}

void movieToeSign::mouseDragged(ofMouseEventArgs& args)
{

}

void movieToeSign::mouseMoved(ofMouseEventArgs& args)
{

}

void movieToeSign::mouseReleased(ofMouseEventArgs& args)
{

}


void movieToeSign::setMovieRect(ofRectangle rect)
{
    movieRect = rect;
    movWidth = movieRect.width;
    movHeight = movieRect.height;
}

void movieToeSign::setColumnRectSize(int size)
{
    columnRectSize = size;
    for(int i = 0; i <eSigns.size(); i++)
    {
        eSigns[i].setColumnRectSize(columnRectSize);
    }

}
void movieToeSign::guiHandler()
{
    //1. create open gui
    //2. if the coords are inside of alread added columns region, go to edit
    //3. if not inside of added columns, create new column
    for(int g = 0; g <eSigns.size(); g++)
    {
        for(int h = 0; h< eSigns[g].eSignPorts.size(); h++)
        {
            if(eSigns[g].eSignPorts[h].eSignRGBColumns.size()>0)
            {
                for (int i =0; i < eSigns[g].eSignPorts[h].eSignRGBColumns.size(); i++)
                {
                    if( eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.inside(mouseX,mouseY))
                    {
                        //x,y is inside the columnRect -> edit

                        //continue;
                        editMode = EDIT;
                        return;
                    }
                }
                //addColumn(8, true);
                saveX = mouseX;
                saveY = mouseY;
                editMode=ADD;
                return;
            }
            else
            {

                //create new
                //addColumn(8, true);
                saveX = mouseX;
                saveY = mouseY;
                editMode=ADD;
                return;
            }
        }
    }
}

editModeType movieToeSign::getEditMode()
{
    return editMode;
}


void movieToeSign::addeSign(string UDPAddress, int numOfPorts)
{
    eSignFixture eSign;
    eSign.setup(UDPAddress, numOfPorts);

    ////////////////////////////////
    eSigns.push_back(eSign);


}

void movieToeSign::addColumn(int fixtureNumber, int portNumber, float x, float y, int LEDNumber, bool direction)
{
    eSigns[fixtureNumber].addColumn(portNumber,x,y,LEDNumber,direction);
}

int movieToeSign::getNumOfeSigns()
{
    return eSigns.size();
}

int movieToeSign::getNumOfLED()
{
    movieLEDNumber = 0;
    for(int i = 0; i < eSigns.size(); i++)
    {
        movieLEDNumber = movieLEDNumber + eSigns[i].getNumOfLED();
    }
    return movieLEDNumber;
}

int movieToeSign::getNumOfLEDinPort(int fixtureNumber, int portNumber)
{
    portLEDNumber = 0;
    portLEDNumber = eSigns[fixtureNumber].eSignPorts[portNumber].getNumOfLED();

    return portLEDNumber;
}

void movieToeSign::setColumnColorFromPixels(unsigned char * pixels)
{
    //get color from tiled image and set colors for the columns
    //if a column is not yet added for a coordinates from image, ignore
    //loop added columns to set column colors based on saved column position

    for(int g = 0; g <eSigns.size(); g++)
    {
        for(int h = 0; h< eSigns[g].eSignPorts.size(); h++)
        {
            for (int i =0; i < eSigns[g].eSignPorts[h].eSignRGBColumns.size(); i++)
            {

                meanCnt=0;
                meanR=0; meanG=0; meanB=0;
                xStart = (int)eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.x;
                yStart = (int)eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.y;
                int rectWidth = columnRectSize;
                int rectHeight= columnRectSize;

                for( int m = 0; m< rectWidth ; m++){
                    for(int n = 0; n<rectHeight ; n++){

                    meanR += pixels[(xStart+m + (yStart+n)*movWidth)*3];
                    meanG += pixels[(xStart+m + (yStart+n)*movWidth)*3 +1];
                    meanB += pixels[(xStart+m + (yStart+n)*movWidth)*3 +2];

                    meanCnt++;
                    }
                }

                meanR/=(float)meanCnt;
                meanG/=(float)meanCnt;
                meanB/=(float)meanCnt;

                eSigns[g].eSignPorts[h].eSignRGBColumns[i].setColor(ofColor((unsigned char)meanR,(unsigned char)meanG,(unsigned char)meanB));
            }
        }
    }
}

void  movieToeSign::draw(float x, float y, drawMode)
{

    //draw selected column
    if(mouseOnMovie){
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(255);
        ofLine(mouseX,mouseY-5,mouseX,mouseY+5);
        ofLine(mouseX-5,mouseY,mouseX+5,mouseY);
        ofPopStyle();
        ofPopMatrix();
    }

    ofPushMatrix();
    ofPushStyle();
 
    //draw saved column
    for(int g = 0; g <eSigns.size(); g++)
    {
        for(int h = 0; h< eSigns[g].eSignPorts.size(); h++)
        {
            for (int i =0; i < eSigns[g].eSignPorts[h].eSignRGBColumns.size(); i++)
            {

                ofFill();
                ofSetColor(eSigns[g].eSignPorts[h].eSignRGBColumns[i].getColor());
                //ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect);
                ofNoFill();
                //TO DO: set color by ports
                ofSetColor(eSigns[g].eSignPorts[h].borderColor);
                ofSetLineWidth(1);
                ofRect(eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect);
                ofDrawBitmapString(ofToString(i),eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.x,eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.y-5);
            }

            ofBeginShape();
            for (int i =0; i < eSigns[g].eSignPorts[h].eSignRGBColumns.size(); i++)
            {

                //ofSetColor(eSigns[g].eSignPorts[h].borderColor);
                ofSetLineWidth(1);
                ofVertex(eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.x,eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.y);

            }
            ofEndShape();

        }
    }

    ofPopStyle();
    ofPopMatrix();

    drawStatus(1100,0,fixtureNumber,portNumber);

    //// eSignUdp packets send
    for(int i=0; i<eSigns.size(); i++) {
        eSigns[i].update();
    }
}

void movieToeSign::drawStatus(float x, float y, int fixNum, int portNum)
{
    ofPushMatrix();
    ofTranslate(x,y);
    ofPushStyle();
    ofSetColor(255);


    ofDrawBitmapString("LED number in esign:"+ofToString(fixNum+1)+" -> port "+ofToString(portNum+1),0,50);
    ofDrawBitmapString(ofToString(getNumOfLEDinPort(fixNum,portNum)),0,70);


    ofDrawBitmapString("Total Number of LEDs ",0,90);
    ofDrawBitmapString(ofToString(getNumOfLED()),0,110);
    ofPopStyle();
    ofPopMatrix();
}


//gui related

void movieToeSign::guiSetup()
{
    gui = hGui::getInstance();

    gui->setup("fonts/frabk.ttf", 9); // In each version of OF there is another font that looks better ...
    int gui_width = 400;
    int gui_height = 400;
    int xx= ofGetWidth() - gui_width-30;
    int yy= gui->margin1+gui->margin3;

	hPanel * mainPanel =
	gui->addPanel("mainPanel", NULL, HGUI_ABSOLUTE_POSITION, xx, yy, gui_width, gui_height, true);

	mainPanel->setVisibleBackground(true);
	gui->setRootWidget(mainPanel);

	gui->addListeners();

    hEvents * events = hEvents::getInstance();

	events->setup();

	events->addObject("movieToeSign", this);

    hLabel * fixtureLabel = gui->addLabel("", mainPanel, HGUI_TOP_LEFT, gui->margin2, 5, "eSign Fixture");
    fixtureButtonBox = gui->addButtonBox("fixtureButtonBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);
    fixtureButtonBox->displayIndexes(true);
    fixtureButtonBox->addItems(9, 1);
  	fixtureButtonBox->selectItem(1); // preselect an item (first item is 1)
  	events->addListener("setFixtureFromGui", this, &movieToeSign::setFixtureFromGui);
  	fixtureButtonBox->setMessage("movieToeSign.setFixtureFromGui");

    hLabel * portLabel = gui->addLabel("", mainPanel, HGUI_NEXT_ROW, gui->margin2, 5, "Port");
    portButtonBox = gui->addButtonBox("portButtonBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);
    portButtonBox->displayIndexes(true);
    portButtonBox->addItems(8, 1);
  	portButtonBox->selectItem(1); // preselect an item (first item is 1)
  	events->addListener("setPortFromGui", this, &movieToeSign::setPortFromGui);
  	portButtonBox->setMessage("movieToeSign.setPortFromGui");

//    hLabel * columnLabel = gui->addLabel("", mainPanel, HGUI_NEXT_ROW, gui->margin2, 5, "Column");
//    columnSlider = gui->addSlider("columnSlider", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 100);
//    columnSlider->setRange(1, 30); columnSlider->setValue(20);
//    columnSlider->setColor(0xFF0000);
//
//    hNumberBox * number1 =
//	gui->addNumberBox("number1", mainPanel, HGUI_ABSOLUTE_POSITION,
//					  columnSlider->getX()+columnSlider->getWidth()+gui->margin3, columnSlider->getY(), gui->numberBoxWidth, "255");
//	number1->setRange(1, 30); number1->setValue(30);
//	columnSlider->setLinkedNumberBox(number1);
//	number1->setLinkedSlider(columnSlider);

    hLabel * ledLabel = gui->addLabel("", mainPanel, HGUI_NEXT_ROW, gui->margin2, 5, "LED Number");
    ledButtonBox = gui->addButtonBox("ledButtonBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);
    ledButtonBox->displayIndexes(true);
    ledButtonBox->addItems(10, 1);
  	ledButtonBox->selectItem(1); // preselect an item (first item is 1)
  	events->addListener("setLEDNumFromGui", this, &movieToeSign::setLEDNumFromGui);
  	ledButtonBox->setMessage("movieToeSign.setLEDNumFromGui");

    upCheckBox = gui->addCheckBox("upCheckBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin1);
    upCheckBox->setRadioEnabled(true);
    upCheckBox->setSelected(true);
    upCheckBox->setSelectColor(0xFF0000);
    hLabel * label0 = gui->addLabel("", mainPanel, HGUI_RIGHT, gui->margin2 ,0, "UP");

    bottomCheckBox = gui->addCheckBox("bottomCheckBox", mainPanel, HGUI_RIGHT, gui->margin3, 0);
    bottomCheckBox->setRadioEnabled(true);
    bottomCheckBox->setSelectColor(0x00FF00);
    hLabel * label1 = gui->addLabel("", mainPanel, HGUI_RIGHT, gui->margin2 ,0, "DOWN");


    upCheckBox->setMessage("movieToeSign.selectItem");
	bottomCheckBox->setMessage("movieToeSign.selectItem");

	upCheckBox->setIndex(1);
	bottomCheckBox->setIndex(2);



    hButton* button1 =
	gui->addButton("ADD", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 100, "ADD");

	button1->setMessage("movieToeSign.start");

	mainPanel->adaptPanelSize(gui->margin2, gui->margin2);

	gui->loadSettings("settings.xml");

    setDarkColors();

    //init select numbers
    fixtureNumber=0;
    portNumber=0;
    columnLEDNumber =8;
    //UP: directon is true
    direction =true;
    fixtureButtonBox->selectItem(fixtureNumber+1);
    portButtonBox->selectItem(portNumber+1);
    ledButtonBox->selectItem(columnLEDNumber);
}




void movieToeSign::exit()
{
// In this example, we save the state of our widgets when the application exits

	hGui * gui = hGui::getInstance();

	gui->saveSettings("settings.xml"); // You can of course call that elsewhere

	// The following widgets can actually be saved:
	// hCheckBox hNumberBox hSlider h2DSlider hListBox hButton_box
	// and the individual sliders of a sliderBox
}

//--------------------------------------------------------------
//					Methods called by widgets
//					(using prototypes defined in hObject.h)
//--------------------------------------------------------------

void movieToeSign::start(void){
	myString = "start";


    if(!mouseOnMovie){
        if(editMode == ADD ){
            addColumn(fixtureNumber,portNumber , saveX, saveY, columnLEDNumber,direction);
            editMode = DONE;
        }
    }
}

void movieToeSign::stop(void){
	myString = "stop";
}

void movieToeSign::clear(void){
	myString = "";
}

void movieToeSign::setLedColor(int* red, int* green,int* blue)
{


}

//--------------------------------------------------------------

void movieToeSign::setValue(double val)
{
	myString = ofToString(val);
}

void movieToeSign::setValueToItem(double val, int index)
{
	myString = ofToString(index) + " =>" + ofToString(val);
}

void movieToeSign::setXY(double x, double y)
{
	myString = ofToString(x) + "\n" + ofToString(y);
	xPct = x; yPct = y;
}

//--------------------------------------------------------------

void movieToeSign::selectItem(int item)
{
	switch(item){
        case 1:
        direction = true;
        break;
        case 2:
        direction = false;
        break;
	}
}

void movieToeSign::itemSetSelected(int item, bool flag)
{
	if(flag == true)
		 myString = ofToString(item) + "(true)";
	else myString = ofToString(item) + "(false)";
}

//--------------------------------------------------------------

void movieToeSign::setLabel(std::string label)
{
	myString = label;
}

void movieToeSign::setText(std::string text)
{
	myString = text; // Not very clever processing...
	// it's just a test
}

void movieToeSign::addText(std::string text)
{
	myString += text; // another possibility, add instead of set text
	// (you have to change setMessage to "addText" to work)
}

void movieToeSign::clearText(void)
{
	myString.clear();
}

void movieToeSign::openItem(int item)
// Open dialogs:
// #1 is a message box
// #2 is an alert
{
	hEvents * events = hEvents::getInstance();

	switch(item) {
		case 1:
			events->sendEvent("msgBoxDialog.clear");
			events->sendEvent("msgBoxDialog.display", "line1");
			events->sendEvent("msgBoxDialog.display", "line2");
			events->sendEvent("msgBoxDialog.display", "line3");
			events->sendEvent("msgBoxDialog.display", "line4");
			events->sendEvent("msgBoxDialog.display", "line5");
			events->sendEvent("msgBoxDialog.display", "line6 (scrolling...)");
			events->sendEvent("msgBoxDialog.display", "line7");
		break;

		case 2:
			events->sendEvent("alertDialog.clear");
			events->sendEvent("alertDialog.display", "Are you ready?");
		break;
	}
}

void movieToeSign::answerDialog(int buttonID)
// Called to process the answer of the alert dialog
{
	switch(buttonID) {
		case 1: myString = "answer = yes"; break;
		case 2: myString = "answer = no";  break;
	}
}


//--------------------------------------------------------------
					// Example of custom listener
//--------------------------------------------------------------

void movieToeSign::setFixtureFromGui(hEventArgs& args)
{
    if(args.values.size() > 0) {
		hEvents * events = hEvents::getInstance(); // We need access to our event engine
        hObject * object = events->getObject(args.objectName);
		if(object == this) {

			hGui * gui = hGui::getInstance(); // We need access to our gui engine

			fixtureNumber = (int)args.values[0];
			fixtureNumber = fixtureNumber-1;

		}
	}
}
void movieToeSign::setPortFromGui(hEventArgs& args)
{
    if(args.values.size() > 0) {
		hEvents * events = hEvents::getInstance(); // We need access to our event engine
        hObject * object = events->getObject(args.objectName);
		if(object == this) {

			hGui * gui = hGui::getInstance(); // We need access to our gui engine

			 portNumber = (int)args.values[0];
			 portNumber =  portNumber-1;

		}
	}
}

void movieToeSign::setLEDNumFromGui(hEventArgs& args)
{
    if(args.values.size() > 0) {
		hEvents * events = hEvents::getInstance(); // We need access to our event engine
        hObject * object = events->getObject(args.objectName);
		if(object == this) {

			hGui * gui = hGui::getInstance(); // We need access to our gui engine

			columnLEDNumber = (int)args.values[0];


		}
	}
}

void movieToeSign::setColors(hEventArgs& args)
{
	// args can have 2 types of variables,
	// 'double' and 'string', each stored in a vector
	// (It was easier and faster to separate the type of variables
	// rather than packing them then for example use tagged unions
	// and it permits also a greater flexibility)

	// When the listener uses one or both of this vectors it has to check its
	// size before using them. (The application can crash when trying to acces an unexisting parameter)

	// Sometimes the widgets send more parameters than needed, and the listener can choose which are usefull to him.

	if(args.values.size() > 0) { // Check the size of the vector of 'value'
		// (because we need 1 parameter, it has to be at least 1, but can be eventually greater
		// it there are external parameters we don't need here)

		// We don't need to check 'args.strings.size()' here, because this method doesn't need
		// named parameters

		hEvents * events = hEvents::getInstance(); // We need access to our event engine

		// Now we verify if the message belong to this object
		hObject * object = events->getObject(args.objectName);
		if(object == this) {
			// (we could eventually create listeners that answer to messages sent to any object (or none)
			// but here we want only to answer messages that belong to 'movieToeSign'

			hGui * gui = hGui::getInstance(); // We need access to our gui engine

			switch((int)args.values[0]) { // Create a different action, depending on the parameter
				case 1:
					cout << "setColors (1)" << endl;
					setDarkColors();
					break;

				case 2:
					cout << "setColors (2)" << endl;
					gui->setDefaultColors();
				break;
			}
		}
	}
}

//--------------------------------------------------------------

void movieToeSign::setDarkColors(void)
// Example of changing the colors of the GUI
{

	hGui * gui = hGui::getInstance();

	gui->setBackgroundColor	(0x333333);
	gui->setBorderColor		(0xCCCCCC);
	gui->setFillColor		(0x555555);
	gui->setAltFillColor	(0x557766);
	gui->setButtonShadowColor(0x999999);

	gui->setScrollHandleColor(0xDDDDDD);
	gui->setScrollButtonColor(0xDDDDDD);
	gui->setTextColor		(0xFFFFFF);
	gui->setTextColor2		(0x000000);
	gui->setAlertTextColor	(0xCCCCCC);

	gui->setDisableColor	(0x999999);
	gui->setEditTextColor	(0x113388);
	gui->setEditTextColor2	(0x113388);
	gui->setEditBackColor	(0xCCDDEE);
	gui->setCaretColor		(0x000000);

	gui->setLabelSelColor	(0xBBBBFF);
	gui->setItemSelColor	(0xBBBBBB);
	gui->setItemSelTextColor(0x333333);
	gui->setTabBoxSelColor	(0x4477CC);
	gui->setButtonBoxSelColor(0x44CC77);

	gui->setCheckBoxColor	(0x44CC77);
	gui->setSliderColor		(0x999999);
	gui->setTwoDSliderColor	(0x33BB66);
	gui->setCounterColor	(0x33BB66);

	gui->setDialogColor		(0xE5E5E5);
	gui->setMessageBoxColor	(0x77FFAA);
	gui->setAlertColor		(0xFF7777);
}
