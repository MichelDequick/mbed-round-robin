#pragma once
#include "Color.h"
#include "RGBCycler.h"
#include "mbed.h"

class RGBLED{
    private:
        Color *color;
        RGBCycler *cycler;
        PwmOut led_red;
        PwmOut led_green;
        // PwmOut led_blue;

    public:
        RGBLED(PinName pin_red, PinName pin_green, PinName pin_blue);
        ~RGBLED(void);
        void setColor(Color *color);
        void cycleRGB(float progress);
        void update(void);


};
