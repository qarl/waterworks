#include "ww.h"



void wwFireSimulator::doIt(const wwMapGray &burn, wwMapGray &fire)
{
  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if (burn.grays[i][j])
	  fire.grays[i][j] = 255;
      }

  blur.doIt(fire, temp);
  blur.doIt(temp, fire);

  
  for (int i = 2; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	fire.grays[i-2][j] = CLIP0(fire.grays[i][j]-10);
      }

}
