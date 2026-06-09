#include "ww.h"


void wwSplit::doIt(const wwMapColor &input, wwMapGray &red,
		   wwMapGray &green, wwMapGray &blue)
{
  WW_MAP_LOOP(i,j)
    {
      red.grays[i][j] = input.colors[i][j][2];
      green.grays[i][j] = input.colors[i][j][1];
      blue.grays[i][j] = input.colors[i][j][0];
    }

}

