#include "controlGui.h"


void controlGui::setup() {
    ofPushStyle();

    hGui * gui = hGui::getInstance();
		// Create and initialize the hGui engine

// Singleton objects use a setup method instead of a constructor

	// void setup(std::string fnt, int size)
	// gui->setup parameters: the default font used by the gui

    gui->setup("fonts/frabk.ttf", 9); // In each version of OF there is another font that looks better ...

    int gui_width = 400;
    int gui_height = ofGetHeight();
    int xx= ofGetWidth() - gui_width;
    int yy= gui->margin1+gui->margin3;

	hPanel * mainPanel =
	gui->addPanel("mainPanel", NULL, HGUI_ABSOLUTE_POSITION, xx, yy, gui_width, gui_height, true);

	mainPanel->setVisibleBackground(true);
	// by default, the background of a panel is not visible, so make it visible

// Let our gui engine know what is our root widget (can also be done or changed later)
// All events will first process the root widget
// Note: A program can eventually set another root widget during its execution

	gui->setRootWidget(mainPanel);
	// void setmainPanel(hWidget * root);

// Let our gui engine respond to draw, keyPressed, mousePressed, mouseDragged and mouseReleased events
// Alternative: instead of using gui->addListeners() one can also call gui->draw(), gui->keyPressed() (etc...)
// in the draw(), keyPressed() (etc...) methods

	gui->addListeners();
	// void addListeners(void);

	//----------------------------------------
	// Create panels and labels:

	int panelSize1 = 200;

	hPanel * panel1 =
	gui->addPanel("", mainPanel, HGUI_TOP_LEFT, gui->margin2, gui->margin1, panelSize1, panelSize1, true);
	hLabel * label1 = gui->addLabel("", panel1, HGUI_TOP_LEFT, 2, 0, "panel1");

	hPanel * panel2 =
	gui->addPanel("", mainPanel, HGUI_RIGHT, gui->margin2, 0, panelSize1, panelSize1, true);
	hLabel * label2 = gui->addLabel("", panel2, HGUI_TOP_LEFT, 2, 0, "panel2");

	hPanel * panel3 =
	gui->addPanel("", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, panelSize1, panelSize1, true);
	hLabel * label3 = gui->addLabel("", panel3, HGUI_TOP_LEFT, 2, 0, "panel3");

	hPanel * panel4 =
	gui->addPanel("", mainPanel, HGUI_RIGHT, gui->margin2, 0, panelSize1, panelSize1, true);

	mainPanel->adaptPanelSize(gui->margin2, gui->margin2);
	// void adaptPanelSize(int x, int y);
	// If an object inside of a panel is bigger than the panel, the panel will grow to have the same size
	// and then add also x,y to its size

	//----------------------------------------
	// Create a checkbox and select it:

	hCheckBox * checkbox1 =
	gui->addCheckBox("checkbox1", panel1, HGUI_BOTTOM, gui->margin2, 0);
	checkbox1->setSelected(true);

	// Let the checkbox control a bool variable
	drawFlag = true; // The variable and the widget have to be the same value at startup
	checkbox1->setBoolVar(&drawFlag);

	// Add a label that explain what the checkbox do
	hLabel * label0 = gui->addLabel("", panel1, HGUI_RIGHT, gui->margin3 ,0, "drawing on/off");

	//----------------------------------------
	// Create 3 sliders:

	slider1 =
	gui->addSlider("slider1", panel1, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 100);
	slider2 =
	gui->addSlider("slider2", panel1, HGUI_BOTTOM, 0, -1, 100);
													// ^ start y of new slider has to be end the y of previous
													// else an extra line is showing

	slider3 =
	gui->addSlider("slider3", panel1, HGUI_BOTTOM, 0, -1, 100);

	// Set the range and value of the sliders
	slider1->setRange(0, 255); slider1->setValue(234);
	slider2->setRange(0, 255); slider2->setValue(234);
	slider3->setRange(0, 255); slider3->setValue(234);

	// Change the color of the sliders
	slider1->setColor(0xFF0000); // slider1->setBackgroundColor(0xFF8888);
	slider2->setColor(0x00FF00); // slider2->setBackgroundColor(0x88FF88);
	slider3->setColor(0x0000FF); // slider3->setBackgroundColor(0x8888FF);

	// Let the sliders control int variables
	red = 234;
	green = 234;
	blue = 234;

	slider1->setIntVar(&red);
	slider2->setIntVar(&green);
	slider3->setIntVar(&blue);


	/* kind of variable that widgets can control:
	 void setIntVar(int *var);
	 void setFloatVar(float *var);
	 void setDoubleVar(double *var);
	 void setBoolVar(bool *var); // used by checkBoxes
	 void unsetVar(void); // Remove previous link to the variable

	 kind of widgets that can control (or be controlled by) variables:
	 hSlider, hNumberBox hCheckBox

	 Note: hNumberBox widgets cannot be controlled by a variable during editing
	 */

	//----------------------------------------
	// Create sliders with value displayed on them:

	hSlider* slider4 = gui->addSlider("slider4", panel1, HGUI_BOTTOM, 0, 15, 100); slider4->setRange(0, 1, 3);
	hSlider* slider5 = gui->addSlider("slider5", panel1, HGUI_BOTTOM, 0, 15, 100); slider5->setRange(0, 1, 3);
	// void hSlider::setRange(double min, double max, int precision)
	// precision: used for the linked object: how many decimal digits to display

	// Create a label and link it to the slider
	hLabel * sliderLabel1 = gui->addLabel("", panel1, HGUI_ABSOLUTE_POSITION, 0, 0, "");
	hLabel * sliderLabel2 = gui->addLabel("", panel1, HGUI_ABSOLUTE_POSITION, 0, 0, "");

	slider4->setLinkedLabel(sliderLabel1, true);
	slider5->setLinkedLabel(sliderLabel2, true);
	// void hSlider::setLinkedLabel(hLabel * labelWidget, bool owningFlag)
	// owningFlag == true means that the label will be displayed and move with the slider

	// shorter and identical:
	// slider4->setLinkedLabel(gui->addLabel("", panel1, HGUI_ABSOLUTE_POSITION, 0, 0, ""), true);
	// slider5->setLinkedLabel(gui->addLabel("", panel1, HGUI_ABSOLUTE_POSITION, 0, 0, ""), true);

	slider4->setValue(0.5); // When a value is set, it is also displayed on the label
	slider5->setValue(0.5);

	xPct = 0.5; yPct = 0.5;
	slider4->setFloatVar(&yPct);
	slider5->setFloatVar(&xPct);


	//----------------------------------------
	// Create a counter and link it to the actual time

	// hCounterLabel widgets can use a special font called counter font
	// if a counter font is set, the counter uses it instead of the default font
	gui->setCounterFont("fonts/verdana.ttf", 16);

	hCounterLabel* counterLabel =
	gui->addCounterLabel("counterLabel", panel1, HGUI_NEXT_ROW, gui->margin2, gui->margin2, "0000");

	// counterLabel->display_days(true);		  // display the days too
	// counterLabel->display_milliseconds(true); // display the milliseconds too

	curTime = 0;
	counterLabel->setIntVar(&curTime);

	//----------------------------------------
	// Create number boxes and link them to the color sliders
	// Link them also to variables

	// Note: In the actual version there is not yet text selection, so it is necessary to use backspace
	// to change the value of a numberBox

	// Warning: in the actual version, HGUI_ABSOLUTE_POSITION can only be used after other definitions
	// in the same panel

	// It would be possible to define the number boxes just after each slider
	// It was only done this way for demonstration purposes

	hNumberBox * number1 =
	gui->addNumberBox("number1", panel1, HGUI_ABSOLUTE_POSITION,
					  slider1->getX()+slider1->getWidth()+gui->margin3, slider1->getY(), gui->numberBoxWidth, "255");

	hNumberBox * number2 =
	gui->addNumberBox("number2", panel1, HGUI_ABSOLUTE_POSITION,
					  slider2->getX()+slider2->getWidth()+gui->margin3, slider2->getY(), gui->numberBoxWidth, "255");

	hNumberBox * number3 =
	gui->addNumberBox("number3", panel1, HGUI_ABSOLUTE_POSITION,
					  slider3->getX()+slider3->getWidth()+gui->margin3, slider3->getY(), gui->numberBoxWidth, "255");

	// Set the range and value of the number boxes
	number1->setRange(0, 255); number1->setValue(234);
	number2->setRange(0, 255); number2->setValue(234);
	number3->setRange(0, 255); number3->setValue(234);

	// Link the number boxes to the color sliders (to display the values)
	slider1->setLinkedNumberBox(number1);
	slider2->setLinkedNumberBox(number2);
	slider3->setLinkedNumberBox(number3);

	// Link the sliders to the number boxes (typing a value update the slider)
	number1->setLinkedSlider(slider1);
	number2->setLinkedSlider(slider2);
	number3->setLinkedSlider(slider3);

	// The following would do the same than slider1->setIntVar in this case,
	// because the 2 objects are linked

	/*
	number1->setIntVar(&red);
	number2->setIntVar(&green);
	number3->setIntVar(&blue);
	 */

// -------------------------------------------------------------------------------------

// Now it's time to work with the events
// hEvents are custom POCO events

	// Create and initialize the events engine. (It's a singleton too)

	hEvents * events = hEvents::getInstance();
	events->setup();

// events->set_verbose(true); // display on the console what the events send
	// (just if you want to show how the messages are sent, and which are their parameters)

	// Add an object to the event engine the object, so it can receive events
	// void hEvents::addObject(std::string objectName, hObject * obj)

	events->addObject("controlGui", this);
	// Here we use testApp as object
	// This is possible because controlGui inherits from hObject
	// Look at controlGui.h to see the implementation

	// Maybe its better to create other objects instead of using controlGui
	// to respond to the messages, in order to avoid conflicts caused
	// by multiple inheritance
	// This permits also to have the same message for different objects
	// and different actions

	//----------------------------------------

	// Create 3 buttons on the second panel:

	hButton* button1 =
	gui->addButton("button1", panel2, HGUI_BOTTOM, gui->margin3, gui->margin3, 100, "start");

	hButton* button2 =
	gui->addButton("button2", panel2, HGUI_BOTTOM, 0, gui->margin3, 100, "stop");

	hButton* button3 =
	gui->addButton("button3", panel2, HGUI_BOTTOM, 0, gui->margin3, 100, "clear");

	// Set the message that the buttons will send when pressed
	// The form of the message is "object.method"
	button1->setMessage("controlGui.start");
	button2->setMessage("controlGui.stop");
	button3->setMessage("controlGui.clear");

	// This works because the start, stop and clear listeners are defined in hEvent.cpp
	// and redefined for controlGui (see below on the next methods)

	// You can also create your own listeners anywhere
	// (I will show that later)

	// With this test, the start, stop and clear methods will just modify a string, so we need to initialize a font for it
	font = new ofTrueTypeFont;
	font->loadFont("fonts/AvantGarde-Book.ttf", 16, true, true);
	myString = "";

	//----------------------------------------

	// Create 3 checkboxes that work like radio buttons

	hCheckBox * checkbox2 =
	gui->addCheckBox("checkbox2", panel2, HGUI_BOTTOM, 0, gui->margin1);
	checkbox2->setRadioEnabled(true);
	checkbox2->setSelected(true); // preselect this one
	checkbox2->setSelectColor(0xFF0000);

	hCheckBox * checkbox3 =
	gui->addCheckBox("checkbox3", panel2, HGUI_RIGHT, gui->margin3, 0);
	checkbox3->setRadioEnabled(true);
	checkbox3->setSelectColor(0x00FF00);

	hCheckBox * checkbox4 =
	gui->addCheckBox("checkbox4", panel2, HGUI_RIGHT, gui->margin3, 0);
	checkbox4->setRadioEnabled(true);
	checkbox4->setSelectColor(0x0000FF);

	// Instead of giving each checkbox another message to send,
	// we use the same message.
	// To distinguish the different checkboxes, we give each of them
	// a different index, and this value will be sent with the message

	// Note: when creating composite objects like listboxes
	// each element will have assigned automatically and index

	// Here we use this feature to indicate that the widgets are part of a virtual group
	// This is specially true when the widgets are used as radio buttons

	checkbox2->setMessage("controlGui.selectItem");
	checkbox3->setMessage("controlGui.selectItem");
	checkbox4->setMessage("controlGui.selectItem");

	checkbox2->setIndex(1);
	checkbox3->setIndex(2);
	checkbox4->setIndex(3);

	//----------------------------------------

	// We can also set the same message to the sliders to different sliders
	// (here, the sliders that control the color)

	slider4->setMessage("controlGui.setValueToItem");
	slider5->setMessage("controlGui.setValueToItem");
	slider4->setIndex(1);
	slider5->setIndex(2);

	//----------------------------------------

	// hTextBox * addTextBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	hTextBox * textBox1 = gui->addTextBox("textBox1", panel2,  HGUI_RIGHT, gui->margin2, 0, 100, "editable textbox");
	textBox1->setMessage("controlGui.setLabel");

	// The message of the textBox will be sent when the user types <return>

	// textBox1->clearAfterReturn(true); // <-- the text will be cleared if this flag is set

	//----------------------------------------

	// Now let's create a text area

	// hTextArea need a fixed size font to work correctly (to be set before any text area creation) :

	// void hGui::setFixedFont(std::string ffnt, int fsize, int fshrk)
	// fshrk = shrink factor: text editing looks better with smaller space between characters

#if OF_VERSION < 7
    gui->setFixedFont("fonts/mono.ttf", 8, 4);
#else
    gui->setFixedFont("fonts/lmmonolt10-bold.otf", 10, 0);
#endif

	// hTextArea *  addTextArea(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height, std::string s);
	hTextArea * textArea1 =
		gui->addTextArea("textArea1", panel2, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 170, 50);

	textArea1->setText(
	    "Editable text areas are also available.\nThey can also be scrollable.\nThe scrollbar is only displayed when needed.", false);
	// (if the flag is 'true', the cursor will be set to the end of the document)

	// Note: in this version, unlike hTextBox and hNumberBox widgets, it is possible to click anywhere
	// to modify the insertion point

	// Now add the buttons used to control the textbox:

		// void addTools(int width, int position, std::string sendStr, std::string clearStr);
		// Add a 'send' and a 'clear' button to a textedit object
		// "width" is the width of each button
		// position: 0 = center, -1 = left, 1 = right

		// When the send button is pushed, the message is sent (with the text as parameter)
		// When the clear button is pushed, the text is cleared
		// An additional message2 can be set to perform another action when the text is cleared

	textArea1->addTools(60, 1, "send", "clear");
	textArea1->setMessage("controlGui.setText");
	textArea1->setMessage2("controlGui.clearText");

	// WARNING !!!!
	// After hTextArea, HGUI_RIGHT and HGUI_BOTTOM does not work correctly
	// Use HGUI_NEXT_ROW and HGUI_NEXT_COL instead

	// -------------------------------------------------------------------------------------

	// Create some composite objects on panel 3

	// hGui::addListBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width)
	hListBox * listBox1 = gui->addListBox("listBox1", panel3, HGUI_BOTTOM, gui->margin2, 0, 100);

	listBox1->addItems(4, "");
	// In my terminology, items are the visible items
	// elements are the total number of objects in the listbox

	listBox1->setElementLabel(1, "one");
	listBox1->setElementLabel(2, "two");
	listBox1->setElementLabel(3, "three");
	listBox1->setElementLabel(4, "four");

	listBox1->addData("five");
	listBox1->addData("six");
	listBox1->addData("seven");
	listBox1->addData("eight");

	listBox1->setMessage("controlGui.setLabel");


	listBox1->selectElement(1); // preselect an element (first element is 1)

	// WARNING !!!!
	// After hListBox, HGUI_RIGHT and HGUI_BOTTOM does not work correctly
	// Use HGUI_NEXT_ROW and HGUI_NEXT_COL instead

//  hButtonBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int item_width, int item_height);
	hButtonBox * buttonBox1 = gui->addButtonBox("buttonBox1", panel3, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);

	buttonBox1->displayIndexes(true);
	// display indexes on the buttonBox
	// (It is possible to have indexes, names or both)

	buttonBox1->addItems(6, 4);
	buttonBox1->selectItem(1); // preselect an item (first item is 1)
	buttonBox1->setMessage("controlGui.itemSetSelected");

	// -------------------------------------------------------------------------------------

	// Create some subpanels just for fun :

	int panelSize2 = 88;

	hPanel * panel5 =
	gui->addPanel("", panel4, HGUI_TOP_LEFT, gui->margin2, gui->margin2, panelSize2, panelSize2, true);
	hLabel * label5 = gui->addLabel("", panel5, HGUI_TOP_LEFT, 2, 0, "panel4.1");

	hPanel * panel6 =
	gui->addPanel("", panel4, HGUI_BOTTOM, 0, gui->margin2, panelSize2, panelSize2, true);
	hLabel * label6 = gui->addLabel("", panel6, HGUI_TOP_LEFT, 2, 0, "panel4.2");

	hPanel * panel7 =
	gui->addPanel("", panel4, HGUI_NEXT_COL, gui->margin2, gui->margin2, panelSize2, panelSize2, true);
	hLabel * label7 = gui->addLabel("", panel7, HGUI_TOP_LEFT, 2, 0, "panel4.3");

	hPanel * panel8 =
	gui->addPanel("", panel4, HGUI_BOTTOM, 0, gui->margin2, panelSize2, panelSize2, true);
	hLabel * label8 = gui->addLabel("", panel8, HGUI_TOP_LEFT, 2, 0, "panel4.4");

	// -------------------------------------------------------------------------------------

	// Now create a tabBox, in order to be able to switch between different tabs

	// Since we changed the size of mainPanel with adaptPanelSize
	// we have to use the same size for the mainTabBox:
	int mainTabBoxWidth = mainPanel->getWidth();

	// hTabBox *  hGui::addTabBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width)
	hTabBox *  mainTabBox =
		gui->addTabBox("mainTabBox", NULL, HGUI_ABSOLUTE_POSITION, xx, -1, mainTabBoxWidth);
	// NULL: the main tabBox has no parent panel
	// HGUI_ABSOLUTE_POSITION : the only possibility for the main tabBox
	// -1: no need to show the upper line

	mainTabBox->addItems(3); // Add the needed number of items (tabs) to the tabBox
	// (item numbers start always with #1)

	// Set the name of the different tabs
	mainTabBox->setItemLabel(1, "PLAY");
	mainTabBox->setItemLabel(2, "EDIT");
	mainTabBox->setItemLabel(3, "TEST");

	mainTabBox->setItemPanel(1, mainPanel); // Let our main panel to be the fist tab
	mainTabBox->selectItem(1);				// and select it

	gui->setRootWidget(mainTabBox); // Let the gui engine know that now its mainTabBox our root widget
	// (Of course, we could do that at the beginning)
	// Note: since tab2 and tab3 have no panel linked to them, clicking on them will do nothing

	// -------------------------------------------------------------------------------------

	// Create our second main panel and link it to the mainTabBox :
	hPanel * mainPanel2 =
		gui->addPanel(
		"mainPanel2", NULL, HGUI_ABSOLUTE_POSITION, xx, gui->margin1+gui->margin3, mainPanel->getWidth(), mainPanel->getHeight(), true);
	mainPanel2->setVisibleBackground(true);
	mainTabBox->setItemPanel(2, mainPanel2);

	// Does the same for the third tab :
	hPanel * mainPanel3 =
		gui->addPanel(
		"mainPanel3", NULL, HGUI_ABSOLUTE_POSITION, xx, gui->margin1+gui->margin3, mainPanel->getWidth(), mainPanel->getHeight(), true);
	mainPanel3->setVisibleBackground(true);
	mainTabBox->setItemPanel(3, mainPanel3);

	// -------------------------------------------------------------------------------------

	// Create a bigger text box in mainPanel2:

	gui->addLabel("", mainPanel2, HGUI_TOP_LEFT, gui->margin2, gui->margin2, "a bigger text box");
	// (if the label has not to be changed, we don't need to keep a reference to it)

	hTextArea * textArea2 =
		gui->addTextArea("textArea2", mainPanel2, HGUI_NEXT_ROW, gui->margin1, 0, 392, 200);

	textArea2->addTools(100, 1, "send", "clear");
	textArea2->setMessage("controlGui.setText");
	textArea2->setMessage2("controlGui.clearText");

	// WARNING !!!!
	// After hTextArea, HGUI_RIGHT and HGUI_BOTTOM does not work correctly
	// Use HGUI_NEXT_ROW and HGUI_NEXT_COL instead

	// Use events to fill the text of the text box :
	// (can be done from everywhere, no need to keep track of the widget adress)

	// In this example, I use different europen languages, to show that accents and other marks can be used
	// For Macintosh users : works only with files, not with keyboard, and file has to be saved as Western ISO Latin1)

	events->sendEvent("textArea2.clearText");
	events->sendEvent("textArea2.setText", "All human beings are born free and equal in dignity and rights. They are endowed with reason and conscience and should act towards one another in a spirit of brotherhood.\n\n");
	events->sendEvent("textArea2.addText", "Tous les \EAtres humains naissent libres et \E9gaux en dignit\E9 et en droits. Ils sont dou\E9s de raison et de conscience et doivent agir les uns envers les autres dans un esprit de fraternit\E9.\n\n");
	events->sendEvent("textArea2.addText", "Alle Menschen sind frei und gleich an W\FCrde und Rechten geboren. Sie sind mit Vernunft und Gewissen begabt und sollen einander im Geist der Br\FCderlichkeit begegnen.\n\n");
	events->sendEvent("textArea2.addText", "Alle mennesker er f\F8dt frie og lige i v\E6rdighed og rettigheder. De er udstyret med fornuft og samvittighed, og de b\F8r handle mod hverandre i en broderskabets \E5nd.\n\n");

	// -------------------------------------------------------------------------------------

	// Create a 2D slider in mainPanel2:

	gui->addLabel("", mainPanel2, HGUI_NEXT_ROW, gui->margin1, 0, "a 2D slider");

	// h2DSlider * hGui::add2DSlider(std::string name, hPanel * parent, int dispMode, int x, int y, int size)
	h2DSlider * my2Dslider = gui->add2DSlider("my2Dslider", mainPanel2,  HGUI_BOTTOM, 0, 0, 152);

	my2Dslider->setRange(0, 1); // default is -1, 1
	my2Dslider->setMessage("controlGui.setXY");

	// -------------------------------------------------------------------------------------

	// Create a subpanel to put more objects

	hPanel * subPanel = gui->addPanel("subPanel", mainPanel2, HGUI_RIGHT, gui->margin2, 0, 241, 152, true);

	// Create 2 buttons that will send their messages to a new listener created in controlGui:

	hButton * actionButton1 = gui->addButton("actionButton1", subPanel, HGUI_RIGHT, gui->margin2, gui->margin2, 104, "set dark colors");
	hButton * actionButton2 = gui->addButton("actionButton2", subPanel, HGUI_RIGHT, gui->margin2, 0, 104, "set default colors");

	// Create a new event listener using the method defined in this file :
	events->addListener("setColors", this, &controlGui::setColors);
	// "setColors" is the name of the method to call
	// 'this' is the object
	// '&controlGui::setColors' is the method

	actionButton1->setMessage("controlGui.setColors"); // remember the format
	actionButton2->setMessage("controlGui.setColors");

	actionButton1->setIndex(1); // the index is used as parameter by the listener
	actionButton2->setIndex(2);

	// Now you can look at void controlGui::setColors(hEventArgs& args)
	// to see how it works

	// -------------------------------------------------------------------------------------

	// Create a slider box inside of mainPanel3:

	// (A SliderBox is a group of sliders with labels displayed on top of it)

	gui->addLabel("", mainPanel3, HGUI_TOP_LEFT, gui->margin2, gui->margin2, "a slider box");

	// hSliderBox *  addSliderBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);
	hSliderBox * sliderBox1 =
		gui->addSliderBox("sliderBox1", mainPanel3, HGUI_NEXT_ROW, gui->margin2, gui->margin1, 200);

	sliderBox1->addSliders(10); // create 10 sliders

	// The default settings (range etc.. can be modified (see in hSliderBox.h)

	// Set the same message to all sliders of the slider box
	// The change the indexes of the sliders, use SliderBox::setStartIndex
	sliderBox1->setMessage("controlGui.setValueToItem");

	// Create a better contrast by changing the background color of the sliders:
	sliderBox1->setBackgroundColor(0xD7D7D7);

// -------------------------------------------------------------------------------------
	// Create  a status bar
	// A status bar is always drawn on the bottom of the window
	// so it does'nt need dispMode and coordinates

	// hStatusBar * addStatusBar(std::string name, hPanel * parent, std::string s)
	hStatusBar * statusBar = gui->addStatusBar("statusBar", mainPanel, "status bar");
	statusBar->setBackgroundColor(0x77FFAA);

	// Add also the same widget to the other tabs:
	mainPanel2->addWidgetToPanel(statusBar);
	mainPanel3->addWidgetToPanel(statusBar);

	// You can do this if you want that the status bar not to be showing:
	// (for example by pressing a key)
	// statusBar->setDisabled(true);

	// -------------------------------------------------------------------------------------

	// Create a message box
	// A message box is a dialog used to display info for the user
	// It opens when the first display message is sent to it

	// Message boxes can be moved and closed by the user
	// They are visible in all tabs

	int msgBoxX     = (ofGetWidth() / 3)  - (gui->checkBoxSize + 2) / 2;
	int msgBoxY     = (ofGetHeight() / 5) - (gui->checkBoxSize + 2) / 2;
	int msgBoxXSize =  ofGetWidth()  / 3;
	int msgBoxYSize =  ofGetWidth()  / 6;

	// hMessageBox * hGui::addMessageBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width, int height)

	hMessageBox * msgBoxDialog =
		gui->addMessageBox("msgBoxDialog", NULL, HGUI_ABSOLUTE_POSITION, msgBoxX, msgBoxY, msgBoxXSize, msgBoxYSize);

	// -------------------------------------------------------------------------------------

	// Create an alert box
	// An alert box is a modal dialog used to make a choice (yes or no)
	// It opens when the a display message is sent to it

	// Alerts can be moved and closed by the user by clicking at a button
	// They are visible in all tabs

	gui->setAlertFont("fonts/verdana.ttf", 14);

	hAlert * alertDialog =
		gui->addAlert("alertDialog", NULL, HGUI_ABSOLUTE_POSITION, msgBoxX-19, msgBoxY+18, msgBoxXSize, msgBoxYSize);

	alertDialog->setMessage("controlGui.answerDialog");  // Set the message to send when the user answer yes (sends also the value 1)
	alertDialog->setMessage2("controlGui.answerDialog"); // Set the message to send when the user answer no  (sends also the value 2)

	// -------------------------------------------------------------------------------------

	// Create buttons to open the dialogs:

	hButton * actionButton3 = gui->addButton("actionButton3", subPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 104, "open message");
	hButton * actionButton4 = gui->addButton("actionButton4", subPanel, HGUI_RIGHT, gui->margin2, 0, 104, "open alert");

	actionButton3->setMessage("controlGui.openItem");
	actionButton4->setMessage("controlGui.openItem");

	actionButton3->setIndex(1); // the index is used as parameter by the openItem listener
	actionButton4->setIndex(2);

	// -------------------------------------------------------------------------------------

// Load the previousely saved settings: (will also sent the message of the widgets)

	gui->loadSettings("settings.xml");

    setDarkColors();
    ofPopMatrix();

    ofPopStyle();
}

// -------------------------------------------------------------------------------------

void controlGui::exit()
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

void controlGui::start(void){
	myString = "start";
}

void controlGui::stop(void){
	myString = "stop";
}

void controlGui::clear(void){
	myString = "";
}

void controlGui::setLedColor(int* red, int* green,int* blue)
{

	slider1->setIntVar(red);
	slider2->setIntVar(green);
	slider3->setIntVar(blue);
}

//--------------------------------------------------------------

void controlGui::setValue(double val)
{
	myString = ofToString(val);
}

void controlGui::setValueToItem(double val, int index)
{
	myString = ofToString(index) + " =>" + ofToString(val);
}

void controlGui::setXY(double x, double y)
{
	myString = ofToString(x) + "\n" + ofToString(y);
	xPct = x; yPct = y;
}

//--------------------------------------------------------------

void controlGui::selectItem(int item)
{
	myString = ofToString(item);
}

void controlGui::itemSetSelected(int item, bool flag)
{
	if(flag == true)
		 myString = ofToString(item) + "(true)";
	else myString = ofToString(item) + "(false)";
}

//--------------------------------------------------------------

void controlGui::setLabel(std::string label)
{
	myString = label;
}

void controlGui::setText(std::string text)
{
	myString = text; // Not very clever processing...
	// it's just a test
}

void controlGui::addText(std::string text)
{
	myString += text; // another possibility, add instead of set text
	// (you have to change setMessage to "addText" to work)
}

void controlGui::clearText(void)
{
	myString.clear();
}

//--------------------------------------------------------------

void controlGui::openItem(int item)
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

void controlGui::answerDialog(int buttonID)
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

void controlGui::setColors(hEventArgs& args)
// This fonction modify the set of colors used by the widgets
// It show how to respond to custom events
// and also how to customize the apparence of the interface
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
			// but here we want only to answer messages that belong to 'controlGui'

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

void controlGui::setDarkColors(void)
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

//--------------------------------------------------------------

void controlGui::update()
{
// The variable curTime is controlled by the counterLabel widget:
	curTime = ofGetElapsedTimeMillis();

// Show how we can change the state of a widget by sending it a message
	hEvents::getInstance()->sendEvent("statusBar.setLabel", "FPS: " + ofToString(ofGetFrameRate(), 2));

// of course, you can also remember the adress of statusBar and use statusBar->setLabel() directly
// but the event system allows not to be dependent on the header files

}

//--------------------------------------------------------------

void controlGui::draw()
{
//// the following variables are controlled by widgets:
//// backColor, drawFlag, xPct, yPct, myString
//
//	ofBackground(red, green, blue);
//
//	if(drawFlag == false) return;
//
//	//------(c)--------------------------------------
//	// (from polygonExample)
//	//       draw a star dynamically
//
//	int nTips = 5 + xPct * 60;
//	int nStarPts = nTips * 2;
//	float angleChangePerPt = TWO_PI / (float)nStarPts;
//	float innerRadius = 0 + yPct*80;
//	float outerRadius = 80;
//	float origx = 525;
//	float origy = 200;
//	float angle = 0;
//
//#if OF_VERSION < 7
//	ofSetColor(0xa16bca);
//#else
//	ofSetHexColor(0xa16bca);
//#endif
//
//	ofBeginShape();
//	for (int i = 0; i < nStarPts; i++){
//		if (i % 2 == 0) {
//			// inside point:
//			float x = origx + innerRadius * cos(angle);
//			float y = origy + innerRadius * sin(angle);
//			ofVertex(x,y);
//		} else {
//			// outside point
//			float x = origx + outerRadius * cos(angle);
//			float y = origy + outerRadius * sin(angle);
//			ofVertex(x,y);
//		}
//		angle += angleChangePerPt;
//	}
//	ofEndShape();
//
//	//---------------------------------
//
//	ofSetColor(0, 0, 0);
//	font->drawString(myString, 440, 20);
}

//--------------------------------------------------------------
void controlGui::keyPressed(int key){
    hGui * gui = hGui::getInstance();

    if (key==' ') gui->hide();
}

//--------------------------------------------------------------
void controlGui::keyReleased(int key){

}

//--------------------------------------------------------------
void controlGui::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void controlGui::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void controlGui::mousePressed(int x, int y, int button){
 	// cout << x << " " << y << endl;

}

//--------------------------------------------------------------
void controlGui::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void controlGui::windowResized(int w, int h){

}
