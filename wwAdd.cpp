#include "ww.h"


void wwAdd::doIt(const wwMapGray &input1, 
		      const wwMapGray &input2,
		      wwMapGray &output)
{

  WW_MAP_LOOP(i,j)
    {
      output.grays[i][j] = input1.grays[i][j] + input2.grays[i][j];
    }
}



void wwAdd::doIt(const wwMapColor &input1, 
		      const wwMapColor &input2,
		      wwMapColor &output)
{

  WW_MAP_LOOP(i,j)
    {
      output.colors[i][j][0] = 
	input1.colors[i][j][0] + input2.colors[i][j][0];
      output.colors[i][j][1] = 
	input1.colors[i][j][1] + input2.colors[i][j][1];
      output.colors[i][j][2] = 
	input1.colors[i][j][2] + input2.colors[i][j][2];


    }
}
