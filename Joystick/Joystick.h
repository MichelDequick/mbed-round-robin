#pragma once
#include "mbed.h"

class Joystick{
    public:
        DigitalIn up;
        DigitalIn down;
        DigitalIn left;
        DigitalIn right;
        DigitalIn center;
    
    private:

    public:
        Joystick(PinName pin_up, PinName pin_down, PinName pin_left, PinName pin_right, PinName pin_center);
        ~Joystick(void);

    private:
};
