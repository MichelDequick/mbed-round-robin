#include "RGBLED.h"
#include "Color.h"
#include "RGBCycler.h"
#include "mbed.h"

RGBLED::RGBLED(PinName pin_red, PinName pin_green, PinName pin_blue) : led_red(pin_red), led_green(pin_green)//, led_blue(pin_blue)
{
    this->color = new Color();
    this->cycler = new RGBCycler();
    
    led_red.period_ms(1);
    led_green.period_ms(1);
    // led_blue.period_ms(1);

    led_red.write(0.0f);
    led_green.write(0.0f);
    // led_blue.write(0.0f);
}

RGBLED::~RGBLED(void)
{
    delete color;
    delete cycler;
}

void RGBLED::update(void)
{
    led_red.write(color->red * color->alfa);
    led_green.write(color->green * color->alfa);
    // led_blue.write(color->blue * color->alfa);
}

void RGBLED::setColor(Color *color)
{
    this->color = color;
    update();
}

void RGBLED::cycleRGB(float progress)
{
    cycler->calculateRGB(progress, color);
    update();
}
