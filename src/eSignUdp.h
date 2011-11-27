#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "crc.h"

#define IP "192.168.1.11"
#define PORT 8001
#define PORT_COUNT 8
#define CLUSTER_COUNT 125
#define DATA_SIZE 1350

#define PIXELS_SIZE PORT_COUNT*CLUSTER_COUNT*3 // 8* 125 * 3

class eSignUdp {
public:
    eSignUdp(string ip, int _port, int _port_count, int _cluster_count, int _data_size);
    ~eSignUdp();


    void setDumpPacket(bool on);
    void setPixels(uint8_t red,uint8_t green, uint8_t blue);
    void setPixel(uint16_t channel, uint8_t red, uint8_t green, uint8_t blue);
    int sizeOfPixels();

    uint16_t sendto();


private:
    char* pixels;

    uint8_t port_count;
    uint16_t cluster_count;
    uint16_t data_size;

    bool isDumpPacket;

    ofxUDPManager udpConnection;
    int send_packet(uint8_t port_count, uint16_t cluster_count, uint8_t packet_size, uint8_t packet_index, uint16_t sent_datas, uint16_t data_size);
    void dump_packet(vector<unsigned char> packet);
};



