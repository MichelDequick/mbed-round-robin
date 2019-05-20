#pragma once
#include "mbed.h"

class Buzzer{
    public:
        PwmOut play;

    private:

    public:
        Buzzer(PinName pin);
        ~Buzzer(void);
        void playTone(int frequency, int time_ms);
        void playNumber(int number);

    private:
    
};
