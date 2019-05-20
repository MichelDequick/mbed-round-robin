#pragma once
#include "mbed.h"

class Potentiometer{
    public:
        AnalogIn value;

    
    private:

    public:
        Potentiometer(PinName pin);
        ~Potentiometer(void);

    private:
};
