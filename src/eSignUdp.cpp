#include "eSignUdp.h"

eSignUdp::eSignUdp(string ip, int _port, int _port_count, int _cluster_count, int _data_size) {
	udpConnection.Create();
	udpConnection.Connect(ip.c_str(),_port);
	//  udpConnection.SetNonBlocking(true);

    pixels = new char[PIXELS_SIZE];
    port_count = _port_count;
    cluster_count = _cluster_count;
    data_size = _data_size;
    isDumpPacket = false;

}

eSignUdp::~eSignUdp() {
    udpConnection.Close();
}


void eSignUdp::setDumpPacket(bool on)
{
    isDumpPacket = on;
}

int eSignUdp::sizeOfPixels(){
    return PIXELS_SIZE/3;
}

void eSignUdp::setPixel(uint16_t channel, uint8_t red, uint8_t green, uint8_t blue)
{
    if (channel > (PIXELS_SIZE/3)) return;
    pixels[channel*3] = red;
    pixels[channel*3+1] = green;
    pixels[channel*3+2] = blue;
}

void eSignUdp::setPixels(uint8_t red,uint8_t green,uint8_t blue)
{
    for(int i=0; i< PIXELS_SIZE ; i=i+3) {
        pixels[i] = red;
        pixels[i+1] = green;
        pixels[i+2] = blue;
    }
}

int eSignUdp::send_packet(uint8_t port_count, uint16_t cluster_count, uint8_t packet_size, uint8_t packet_index, uint16_t sent_datas, uint16_t data_size)
{
    vector<unsigned char> packet;
    uint16_t crc=0;

    packet.push_back(0x16);
    packet.push_back(0x16);
    packet.push_back(0x16);
    packet.push_back(0x16);

    packet.push_back(0x00);
    packet.push_back(0x00);
    packet.push_back(0x30);

    packet.push_back((data_size+28)&0xff);
    packet.push_back(((data_size+28)&0xff00)>>8);

    packet.push_back(0x00);
    packet.push_back(0x00);

    packet.push_back(0x01);
    packet.push_back(port_count);

    for(int i=0; i< 8; i++) {
        packet.push_back(cluster_count&0xff);
        packet.push_back((cluster_count&0xff00)>>8);
    }
    packet.push_back(0x00);
    packet.push_back(0x00);

    packet.push_back((packet_size<<4)+packet_index);
    packet.push_back(0x00);

    packet.push_back(sent_datas&0xff);
    packet.push_back((sent_datas&0xff00)>>8);

    packet.push_back(data_size&0xff);
    packet.push_back((data_size&0xff00)>>8);

    for(int i=0; i< data_size; i++) {
        packet.push_back(pixels[sent_datas+i]);
    };

    crc = build_crc_ccitt(&packet[4],packet.size()-4);
    packet.push_back(crc >> 8);
    packet.push_back(crc & 0xff);
    packet.push_back(0xf5);

    if (isDumpPacket) dump_packet(packet);

    return udpConnection.Send((const char*)&packet[0],packet.size());
}

uint16_t eSignUdp::sendto() {
    uint16_t remain_data_size = (3 * port_count * cluster_count) % data_size;

    // TODO: 4개 인경우는 패킷을 4개로 잘라야함.
    send_packet(port_count,cluster_count,3,1,0,data_size);
    send_packet(port_count,cluster_count,3,2,data_size,data_size);
    send_packet(port_count,cluster_count,3,3,data_size*2,remain_data_size);
}

void eSignUdp::dump_packet(vector<unsigned char> packet)
{
  cout << "packet size:" <<std::endl;
  cout << packet.size() << std::endl;

  for (int i=0; i<packet.size(); i++) {
    cout << "0x";
    cout << hex << int(packet[i]);
    cout << ", ";
  }
  cout << endl;
}

