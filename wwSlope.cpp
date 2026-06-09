#include "ww.h"


// this code doesn't set the slope of the borders.  i'm too
// lazy right now.

void wwSlope::doIt(const wwMapGray &input, wwMapVector &output)
{
  for (int i = 1; i < WW_HEIGHT -1; i++)
    for (int j = 1; j < WW_WIDTH -1; j++)
      {
	output.vectors[i][j][0] = 
	  (input.grays[i-1][j] - input.grays[i+1][j]) >> 1;
	output.vectors[i][j][1] = 
	  (input.grays[i][j-1] - input.grays[i][j+1]) >> 1;
      }
}

