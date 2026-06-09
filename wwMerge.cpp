#include "ww.h"

void wwMerge::doIt(const wwMapGray &red,
		   const wwMapGray &green,
		   const wwMapGray &blue,
		   wwMapColor &output)
{
  WW_MAP_LOOP(i,j)
    {
      output.colors[i][j][2] = red.grays[i][j];
      output.colors[i][j][1] = green.grays[i][j];
      output.colors[i][j][0] = blue.grays[i][j];
    }

}

