#include "ww.h"


void wwRemapGrayColor::doIt(const wwMapGray &input, wwMapColor &output)
{
  WW_MAP_LOOP(i,j)
    for(int c=0; c < 3; c++)
      {
	output.colors[i][j][c] = 
	  lookup[WWREMAPGRAYCOLOR(input.grays[i][j])][c];
      }
}
