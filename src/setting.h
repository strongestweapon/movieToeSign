#ifndef SETTING_H
#define SETTING_H

#include "ofxXmlSettings.h"
#include "eSignPort.h"
#include "eSignRGBColumn.h"

class Setting
{
    public:
        Setting();
        virtual ~Setting();
        vector <eSignPort> loadPorts(string UDPaddress, int portId);
        void savePorts(string UDPaddress, const vector <eSignPort>& eSignPorts);

    protected:
    private:
        string getXmlFileName(string UDPaddress);
        ofxXmlSettings XML;
        string message;
};

#endif // SETTING_H
