#include "ww.h"


void wwRemapGray::doIt(const wwMapGray &input, wwMapGray &output)
{
  WW_MAP_LOOP(i,j)
    {
      output.grays[i][j] = lookup[WWREMAPGRAY(input.grays[i][j])];
    }
}


void wwRemapGray::doIt(const wwMapColor &input, wwMapColor &output)
{
  WW_MAP_LOOP(i,j)
    {
      output.colors[i][j][0] = lookup[WWREMAPGRAY(input.colors[i][j][0])];
      output.colors[i][j][1] = lookup[WWREMAPGRAY(input.colors[i][j][1])];
      output.colors[i][j][2] = lookup[WWREMAPGRAY(input.colors[i][j][2])];
    }
}
