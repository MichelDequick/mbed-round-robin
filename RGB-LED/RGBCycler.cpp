#include "RGBCycler.h"

RGBCycler::RGBCycler(void)
{

}

void RGBCycler::calculateRGB(float progress, Color *color)
{
  color->red = redCurve(progress);
  color->green = greenCurve(progress);
  color->blue = blueCurve(progress);
}

float RGBCycler::redCurve(float progress)
{
  float value = 0;

  if(progress < 0.66)
  {
    value = (float) 0.5*sin(3*M_PI*(progress-(1.0/6.0)))+0.5;
  }
  return value;
}

float RGBCycler::greenCurve(float progress)
{
  float value = 0;

  if(progress > 0.33)
  {
    progress = progress - 0.33;
    value = (float) 0.5*sin(3*M_PI*(progress-(1.0/6.0)))+0.5;
  }
  return value;
}

float RGBCycler::blueCurve(float progress)
{
  float value = 0;

  if(progress > 0.66)
  {
    progress = progress - 0.66;
    value = (float) 0.5*sin(3*M_PI*(progress-(1.0/6.0)))+0.5;
  }
  else if(progress < 0.33)
  {
    progress = progress + 0.33;
    value = (float) 0.5*sin(3*M_PI*(progress-(1.0/6.0)))+0.5;
  }
  return value;
}
