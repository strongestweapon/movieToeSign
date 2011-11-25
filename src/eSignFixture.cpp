#include "eSignFixture.h"

eSignFixture::eSignFixture()
{
    ofRegisterMouseEvents(this);
    UDPAddress="168.33.44.1";
    fixtureColor = ofColor(0,0,0);
    columnRectSize = 10;
     movWidth = 320;
     movHeight =240;
    bAddColumn = false;
}

eSignFixture::~eSignFixture()
{
    //dtor
}



void eSignFixture::mousePressed(ofMouseEventArgs& args)
{
    //cout << args.x << std::endl;
    posX = args.x;
    posY= args.y;

    cout << addColumnGui() << std::endl;
}

void eSignFixture::mouseDragged(ofMouseEventArgs& args)
{

}

void eSignFixture::mouseMoved(ofMouseEventArgs& args)
{

}

void eSignFixture::mouseReleased(ofMouseEventArgs& args)
{

}



void eSignFixture::setup(string address, ofColor c)
{
    UDPAddress = address;
    fixtureColor=c;
}

int eSignFixture::addColumnGui()
{
    //1. create open gui
    //2. if the coords are inside of alread added columns region, go to edit
    //3. if not inside of added columns, create new column
    if (posX <  movWidth - columnRectSize &&posY <  movHeight - columnRectSize ){
        if(eSignRGBColumns.size()>0)
        {
            for (int i =0; i < eSignRGBColumns.size(); i++)
            {
                if( posX > eSignRGBColumns[i].columnRect.x && posX< eSignRGBColumns[i].columnRect.x +eSignRGBColumns[i].columnRect.width && posY > eSignRGBColumns[i].columnRect.y && posY< eSignRGBColumns[i].columnRect.y +eSignRGBColumns[i].columnRect.height)
                {
                    //x,y is inside the columnRect -> edit
                    cout << "edit" << std::endl;
                    //continue;
                    return 0;
                }
            }
            addColumn(8, true);
            return 1;
        }
        else
        {

            //create new
            addColumn(8, true);
            return 2;
        }
    }
    else{
        cout << "out of range" << std::endl;
        return -1;
    }
}



void eSignFixture::addColumn(int LEDNumber, bool direction)
{

    //2. instantiate a column
    //3. setup column based on inputs from gui and formerly added number of columns
    //4. push column object to eSignFixture
    eSignRGBColumn column;
    column.setup(posX, posY, LEDNumber, direction,columnRectSize);
    eSignRGBColumns.push_back(column);
    //bAddColumn = false;

}

void eSignFixture::setColorFromPixels( unsigned char * pixels)
{
    //get color from tiled image and set colors for the columns
    //if a column is not yet added for a coordinates from image, ignore
    //loop added columns to set column colors based on saved column position


    for (int i =0; i < eSignRGBColumns.size(); i++)
    {

        meanCnt=0;
        meanR=0; meanG=0; meanB=0;
        xStart = (int)eSignRGBColumns[i].columnRect.x;
        yStart = (int)eSignRGBColumns[i].columnRect.y;
        int rectWidth = columnRectSize;
        int rectHeight= columnRectSize;

//        if((xStart+columnRectSize) > movWidth) rectWidth = movWidth%columnRectSize;
//        else rectWidth=columnRectSize;
//
//
//        if((yStart+columnRectSize) > movHeight) rectHeight = movHeight%columnRectSize;
//        else rectHeight=columnRectSize;


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




        eSignRGBColumns[i].setColor(ofColor((unsigned char)meanR,(unsigned char)meanG,(unsigned char)meanB));
    }


}

void eSignFixture::draw()
{

         for (int i =0; i < eSignRGBColumns.size(); i++)
        {
        ofPushMatrix();
        ofPushStyle();
        ofFill();
        ofSetColor(eSignRGBColumns[i].getColor());
        //ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(eSignRGBColumns[i].columnRect);
        ofNoFill();
        ofSetColor(fixtureColor);
        ofRect(eSignRGBColumns[i].columnRect);
        ofDrawBitmapString(ofToString(i),eSignRGBColumns[i].columnRect.x,eSignRGBColumns[i].columnRect.y-5);
        ofPopStyle();
        ofPopMatrix();
        }

        ofPushMatrix();
        ofPushStyle();
        ofSetColor(fixtureColor);
        ofBeginShape();
         for (int i =0; i < eSignRGBColumns.size(); i++)
        {


        ofVertex(eSignRGBColumns[i].columnRect.x,eSignRGBColumns[i].columnRect.y);

        }
        ofEndShape();
        ofPopStyle();
        ofPopMatrix();

 }
