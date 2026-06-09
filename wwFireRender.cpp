#include "ww.h"

#define WW_FIRE_FLICKERFRAMES 10



wwFireRender::wwFireRender() : gradient(wwGradientFilePPM("firegradient.ppm"))
{
  wwMapGray n[WW_FIRE_FLICKERFRAMES];

  // build the flicker warp
  noise.doIt(1, 18, 36, 0.5, 1, 0.1,  WW_FIRE_FLICKERFRAMES, n);

  wwSlope slope;
  flicker = new wwMapVector[WW_FIRE_FLICKERFRAMES];
  for (int f = 0; f < WW_FIRE_FLICKERFRAMES; f++)
    slope.doIt(n[f], flicker[f]);

  frame = 0;
}


wwFireRender::~wwFireRender()
{
  delete [] flicker;
}


void wwFireRender::doIt(const wwMapGray &fire, wwMapColor &output)
{

  wwMapGray fireflicker1;
  warp.doIt(fire, flicker[frame], fireflicker1);

  wwMapGray fireflicker2;
  warp.doIt(fire, flicker[(frame + WW_FIRE_FLICKERFRAMES/2) 
			  % WW_FIRE_FLICKERFRAMES], fireflicker2);


  wwMapGray fireflicker;

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      fireflicker.grays[i][j] = (fireflicker1.grays[i][j] +
				    fireflicker2.grays[i][j]) / 2;


  frame++;
  if (frame >= WW_FIRE_FLICKERFRAMES)
    frame = 0;



  gradient.doIt(fireflicker, output);
}
