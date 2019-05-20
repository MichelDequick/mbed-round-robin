#include "Potentiometer.h"
#include "mbed.h"

/**
 * Constructor of Potentiometer class
 * @param pin The pin to witch the potentiometer is connected
 */
Potentiometer::Potentiometer(PinName pin) : value(pin)
{ 

}

/**
 * Deconstructor of Potentiometer class
 */
Potentiometer::~Potentiometer(void)
{

}
