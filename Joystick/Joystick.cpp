#include "Joystick.h"
#include "mbed.h"

/**
 * Constructor of Joystick class
 * @param pin_up The pin to witch the up button is connected
 * @param pin_down The pin to witch the down button is connected
 * @param pin_left The pin to witch the left button is connected
 * @param pin_richt The pin to witch the right button is connected
 * @param pin_center The pin to witch the center button is connected
 */
Joystick::Joystick(PinName pin_up, PinName pin_down, PinName pin_left, PinName pin_right, PinName pin_center) : up(pin_up), down(pin_down), left(pin_left), right(pin_right), center(pin_center)
{ 

}

/**
 * Deconstructor of Joystick class
 */
Joystick::~Joystick(void)
{

}
