#include <math.h>
#include <stdlib.h>
#include "ww.h"

wwWaterSpigot::wwWaterSpigot(float position, float size, float flow,
			     float amp, float freq)
{
  p = (int)(WW_WATER_WIDTH * position);
  s = (int)(WW_WATER_WIDTH * size);
  f = flow;
  a = (int)(WW_WATER_WIDTH * amp);
  fr = freq;
}

void wwWaterSpigot::doIt(wwMapValue &water)
{
  int w = (int)(s * (sin(t*fr*0.87)+1.0)/2.0);

  for (int i = -w/2; i < w/2; i++)
    {
      int x = (int)(p + a * (sin(t*fr) + sin(t*fr*1.13)) / 2.0);

      if ((float)((rand() % 1000)/1000.0) < f)
	water.values[1][i+x] = 255;

    }
  t++;
}
