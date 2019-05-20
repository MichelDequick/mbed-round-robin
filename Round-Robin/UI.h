#pragma once
#include "mbed.h"
#include "C12832.h"
#include "Joystick.h"

class UI{
    public:
        C12832 * lcd;
        bool dark_theme;

    private:

    public:
        UI(C12832 * lcd);
        ~UI(void);

        void darkTheme(bool dark);
        void background();
        void title(char * title);
        void temperature(char * title, float temp);
        void alert(void);
        void promptNextHop(Joystick * joystick, char * next_hop_ip);


    private:
};
