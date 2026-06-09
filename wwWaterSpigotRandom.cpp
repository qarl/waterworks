#include <stdlib.h>
#include <math.h>
#include "ww.h"


static float frand()
{
  return (float)((rand() % 100000)/100000.0);
}


wwWaterSpigotRandom::wwWaterSpigotRandom()
{
  float flow = pow(frand(), 2);
  float size = frand() * 0.05;
  float amp  = frand() * 0.2;
  float freq = frand() * 0.02;

  float margin = size + amp;

  float position = frand() * (1.0 - 2.0 * margin) + margin;

  spigot = new wwWaterSpigot(position, size, flow, amp, freq);
}

wwWaterSpigotRandom::~wwWaterSpigotRandom()
{
  delete spigot;
}


void wwWaterSpigotRandom::doIt(wwMapValue &water)
{
  spigot->doIt(water);
}


