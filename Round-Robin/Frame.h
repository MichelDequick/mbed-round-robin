#pragma once
#include "mbed.h"

#define FRAME_SOF_1     0xAA
#define FRAME_SOF_2     0xBB
#define FRAME_EOF_1     0xCC
#define FRAME_EOF_2     0xDD


class Frame{
    public:
        char * data;

        char len;
        char idd;
        int16_t tmp;
        char pwm;
        char tun;
        char id[32];
        char crc;


    private:

    public:
        Frame(char * data);
        ~Frame(void);

        void decode(void);
        void checkCRC(void);
        void calculateCRC(void);
        void generate(char * data);

    private:
};
