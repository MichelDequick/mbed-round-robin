#pragma once

#include <math.h>

#include "Color.h"

class RGBCycler{
    private:
      float redCurve(float progress);
      float greenCurve(float progress);
      float blueCurve(float progress);

    public:
      RGBCycler(void);
      void calculateRGB(float progress, Color *color);
};
