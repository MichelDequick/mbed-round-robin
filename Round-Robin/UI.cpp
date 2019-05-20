#include "UI.h"
#include "mbed.h"
#include "C12832.h"
#include "joystick.h"

UI::UI(C12832 * lcd)
{ 
    this->lcd = lcd;
    dark_theme = false;
}

UI::~UI(void)
{

}

void UI::darkTheme(bool dark)
{
    this->dark_theme = dark;
    lcd->invert(dark);
}

void UI::background()
{
    lcd->cls();
    lcd->rect(1,1,126,30,true);
}

void UI::title(char * title)
{
    background();
    lcd->locate(64-(strlen(title)*5/2), 11);    // Center text
    lcd->printf(title);
}

void UI::temperature(char * title, float temp)
{
    background();
    lcd->locate(64-(strlen(title)*5/2), 11);    // Center text
    lcd->printf(title, temp);
}

void UI::alert(void)
{
    for(int i = 0; i <= 5; i++){
        dark_theme = !dark_theme;
        lcd->invert(dark_theme);
        ThisThread::sleep_for(250);
    }
}

void UI::promptNextHop(Joystick * joystick, char * next_hop_ip)
{
    bool update = true;
    int8_t unsigned next_hop[4] = {192,168,0,109};  // Todo: Get current next hop ip
    int8_t n_octet = 3; 

    background();
    lcd->locate(20, 4);
    lcd->printf("Next hop IP address");

    while(!joystick->center){

        if(joystick->up){
            next_hop[n_octet]++;
            update = true;
            }

        if(joystick->down){
            next_hop[n_octet]--;
            update = true;
            }
        
        if(joystick->left){
            n_octet--;
            update = true;
        }

        if(joystick->right){
            n_octet++;
            update = true;
        }

        if(n_octet > 3){n_octet = 0;}
        if(n_octet < 0){n_octet = 3;}

        if(update){
            lcd->fillrect(31,16,99,26,false);
            lcd->locate(32, 17);
            lcd->printf("%.3i.%.3i.%.3i.%.3i", (int) next_hop[0], (int) next_hop[1], (int) next_hop[2], (int) next_hop[3]);
            switch(n_octet) {
            case 0 : lcd->rect(31,16,48,26,true);
                    break;
            case 1 : lcd->rect(48,16,65,26,true);
                    break;
            case 2 : lcd->rect(65,16,82,26,true);
                    break;
            case 3 : lcd->rect(82,16,99,26,true);
                    break;
            }
            update = false;
            sprintf(next_hop_ip, "%i.%i.%i.%i", next_hop[0], next_hop[1], next_hop[2], next_hop[3]);
            ThisThread::sleep_for(150);
        }
    }
}


