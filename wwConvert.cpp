#include "ww.h"

void wwConvert::doIt(const wwMapColor &input, wwMapGray &output)
{
  WW_MAP_LOOP(i,j)
    {
      output.grays[i][j] = (wwGray)((int)(input.colors[i][j][0] +
					  input.colors[i][j][1] +
					  input.colors[i][j][2]) / 3);
    }
}

