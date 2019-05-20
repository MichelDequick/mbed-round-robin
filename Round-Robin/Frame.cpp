#include "Frame.h"
#include "mbed.h"

Frame::Frame(char * data)
{ 
    this->data = data;
    memset(id, 0x00, 32);
}

Frame::~Frame(void)
{

}

void Frame::decode(void)
{
    len = data[2];
    idd = data[3];
    tmp = (data[4] << 8) + data[5];;
    pwm = data[6];
    tun = data[7];
    for(int i = 8; i < (strlen(data) - 3); i++) {
        id[i-8] = data[i];
    }
    crc = data[strlen(data)-4];
}

void Frame::checkCRC(void)
{
    
}

void Frame::calculateCRC(void)
{
    
}


void Frame::generate(char * data)
{
    memset(data, 0x00, 256);
    data[0] = FRAME_SOF_1;
    data[1] = FRAME_SOF_2;
    data[2] = len;
    data[3] = idd;

    data[4] = 1;
    data[5] = 203;

    // data[4] = tmp >> 8;
    // data[5] = tmp & 0xFF;

    data[6] = pwm;
    data[7] = tun;
    // for(int i = 0; i < (strlen(id)); i++) {
    //     data[7 + i] = id[i];
    // }

    data[8] = 108;
    data[9] = crc;
    data[10] = FRAME_EOF_1;
    data[11] = FRAME_EOF_2;

    // data[6 + strlen(id) + 1] = 109;
    // data[6 + strlen(id) + 2] = crc;
    // data[6 + strlen(id) + 3] = FRAME_EOF_1;
    // data[6 + strlen(id) + 4] = FRAME_EOF_2;

    for(int i = 0; i < (strlen(data)); i++) {
        printf("Data[%i]: %i\n\r", i, data[i]);
    }
}

