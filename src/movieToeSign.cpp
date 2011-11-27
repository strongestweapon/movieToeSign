#include "movieToeSign.h"

movieToeSign::movieToeSign()
{
    ofRegisterMouseEvents(this);
    editMode = 0;
}

movieToeSign::~movieToeSign()
{
    //dtor
}

void movieToeSign::mousePressed(ofMouseEventArgs& args)
{
    mouseX = args.x;
    mouseY = args.y;
    guiHandler();
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
}

void movieToeSign::guiHandler()
{
    //1. create open gui
    //2. if the coords are inside of alread added columns region, go to edit
    //3. if not inside of added columns, create new column
    if (mouseX <  movieRect.width - columnRectSize && mouseY <  movieRect.height - columnRectSize )
    {
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
                            cout << "edit" << std::endl;
                            //continue;
                            editMode = 0;
                            return;
                        }
                    }
                    //addColumn(8, true);
                    editMode=1;
                    return;
                }
                else
                {

                    //create new
                    //addColumn(8, true);
                    editMode=2;
                    return;
                }
            }
        }
    }
    else{
        cout << "out of range" << std::endl;
        editMode= -1;
        return;
    }
}

int movieToeSign::getEditMode()
{
    return editMode;
}


void movieToeSign::addeSign(string UDPAddress, int numOfPorts)
{
    eSignFixture eSign;
    eSign.setup(UDPAddress, numOfPorts);
    eSign.addColumn(1,10,10,8,true);
    eSign.addColumn(2,10,10,8,true);
    eSign.addColumn(3,10,10,8,true);
    eSign.addColumn(4,10,10,8,true);
    eSign.addColumn(5,10,10,8,true);
    eSign.addColumn(6,10,10,8,true);
    eSign.addColumn(7,10,10,8,true);

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

                meanR/=meanCnt;
                meanG/=meanCnt;
                meanB/=meanCnt;

                eSigns[g].eSignPorts[h].eSignRGBColumns[i].setColor(ofColor((unsigned char)meanR,(unsigned char)meanG,(unsigned char)meanB));
            }
        }
    }
}

void  movieToeSign::draw(float x, float y, drawMode)
{

    for(int g = 0; g <eSigns.size(); g++)
    {
        for(int h = 0; h< eSigns[g].eSignPorts.size(); h++)
        {
            for (int i =0; i < eSigns[g].eSignPorts[h].eSignRGBColumns.size(); i++)
            {

                ofPushMatrix();
                ofPushStyle();
                ofFill();
                ofSetColor(eSigns[g].eSignPorts[h].eSignRGBColumns[i].getColor());
                //ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect);
                ofNoFill();
                //TO DO: set color by ports
                //ofSetColor(eSigns[g].eSignPorts[h].fixtureColor);
                ofRect(eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect);
                ofDrawBitmapString(ofToString(i),eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.x,eSigns[g].eSignPorts[h].eSignRGBColumns[i].columnRect.y-5);
                ofPopStyle();
                ofPopMatrix();


            }
        }
    }
    cout << "-----------" << std::endl;

    for(int i=0; i<8; i++) {
        eSigns[0].eSignPorts[i].setColor(ofColor(255,0,0));
    }

     //// eSignUdp packets send
    for(int i=0; i<eSigns.size(); i++) {
        eSigns[i].update();
    }

}

