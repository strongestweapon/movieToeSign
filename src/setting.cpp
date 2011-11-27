#include "setting.h"

Setting::Setting()
{
    //ctor
}

Setting::~Setting()
{
    //dtor
}

vector <eSignPort> Setting::loadPorts(string UDPaddress, int portId)
{
    string xmlFileName = getXmlFileName(UDPaddress);
    vector <eSignRGBColumn> eSignColumns;
    vector <eSignPort> eSignPorts;
    // XML
    if( XML.loadFile(xmlFileName) ){
		message = xmlFileName + " loaded!";
	} else {
		message = "unable to load " + xmlFileName + " check data/ folder";
	}
    cout << message << std::endl;

	int numberOfColumns = XML.getNumTags("COLUMN");
	int numberOfPorts = XML.getNumTags("PORT");

    if(numberOfColumns > 0){ //TODO 조건추가: && 175/8 이 넘지 않는다.
        for(int i = 0; i < numberOfColumns; i++){
					//the last argument of getValue can be used to specify
					//which tag out of multiple tags you are refering to.
					int x = XML.getValue("COLUMN:X", 0, i);
					int y = XML.getValue("COLUMN:Y", 0, i);
					int size = XML.getValue("COLUMN:SIZE", 0, i);
					int red = XML.getValue("COLUMN:RED",255,i);
					int green = XML.getValue("COLUMN:GREEN",255,i);
					int blue = XML.getValue("COLUMN:BLUE",255,i);
                    // int direction = XML.getValue("COLUMN:DIRECTION",1,i) == 1 ?1:-1;

//                    eSignRGBColumn es;
//                    es.setup(x,y,size,1);
//                    es.setPosition(x,y);
//                    es.setColor(red,green,blue);
//                    eSignColumns.push_back(es);
        }
    }

    return eSignPorts;
}

void Setting::savePorts(string UDPaddress, const vector <eSignPort>& eSignPorts)
{
    cout << ofToString(
                       eSignPorts.size()
    ) <<std::endl;

    string xmlFileName = getXmlFileName(UDPaddress);

    // XML
    if( XML.loadFile(xmlFileName) ){
		message = "column.xml loaded!";
	} else {
		message = "unable to load column.xml check data/ folder";
	}

    XML.clear();
    cout << xmlFileName << std::endl;

    for (int i=0; i < eSignPorts.size(); i++) {
        eSignPort port = eSignPorts[i];
// port 로 부터 column을 가져 온다.
        eSignRGBColumn e = port.eSignRGBColumns[0];

        XML.addTag("COLUMN");
        XML.setValue("COLUMN:ID", i, i);
        XML.setValue("COLUMN:SIZE", e.RGBLedNumber, i);
        XML.setValue("COLUMN:X", e.posX, i);
        XML.setValue("COLUMN:Y", e.posY, i);
       // XML.setValue("COLUMN:DIRECTION", e.getDirection(), i); // upward.
        XML.setValue("COLUMN:RED", e.getColor().r, i );
        XML.setValue("COLUMN:GREEN", e.getColor().g, i );
        XML.setValue("COLUMN:BLUE", e.getColor().b, i );
    }
    XML.saveFile(xmlFileName);
}


string Setting::getXmlFileName(string UDPaddress)
{
    return string(UDPaddress+"_columns.xml");
}
