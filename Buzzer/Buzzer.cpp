#include "Buzzer.h"
#include "mbed.h"

/**
 * Constructor of buzzer class
 * @param pin The pin to witch the buzzer is connected
 */
Buzzer::Buzzer(PinName pin) : play(pin)
{ 
    // Make sure buzzer is off
    play=0;
}

/**
 * Deconstructor of buzzer class
 */
Buzzer::~Buzzer(void)
{

}

/**
 * Play a tone on the buzzer
 * @param frequency frequency at witch to play the tone
 * @param time_ms Time to play the tone for in ms
 */
void Buzzer::playTone(int frequency, int time_ms)
{
    play.period(1.0/ (float) frequency);
    play = 0.5;
    ThisThread::sleep_for(time_ms);
    play = 0;
}

/**
 * Play a tone from a predefined list
 * @param number the tone to play
 */
void Buzzer::playNumber(int number) 
{
    static const int frequency[] = { 110, 110, 100, 98, 130, 110, 98, 130, 110, 165, 165, 165, 175, 130, 104, 98, 130};
    static const int length[] = { 480, 480, 480, 360, 120, 480, 360, 120, 960, 480, 480, 480, 360, 120, 480, 360, 120};
    static const int delay[] = {100, 100, 100, 75, 100, 100, 75, 100, 100, 100, 100, 100, 75, 100, 100, 75, 100};

    playTone(frequency[number], length[number]);
    ThisThread::sleep_for(delay[number]);
}