#include "ww.h"

wwRub::wwRub(int l, int d, float b) : 
  lightblur(wwBlurBox(l)), 
  darkblur(wwBlurBox(d))
{
  bias = (wwGray) (WW_GRAY_NUM * 3 * b);
}

void wwRub::doIt(const wwMapColor &input, wwMapColor &output)
{
  wwMapGray temp;

  doIt(input, temp);

  WW_MAP_LOOP(i,j)
    {
      if (!temp.grays[i][j])
	{
	  output.colors[i][j][0] = light.colors[i][j][0];
	  output.colors[i][j][1] = light.colors[i][j][1];
	  output.colors[i][j][2] = light.colors[i][j][2];
	}
      else
	{
	  output.colors[i][j][0] = dark.colors[i][j][0];
	  output.colors[i][j][1] = dark.colors[i][j][1];
	  output.colors[i][j][2] = dark.colors[i][j][2];
	}
    }
}


void wwRub::doIt(const wwMapColor &input, wwMapGray &output)
{
  lightblur.doIt(input, light);
  darkblur.doIt(input, dark);

  WW_MAP_LOOP(i,j)
    {
      if((light.colors[i][j][0] +
	  light.colors[i][j][1] +
	  light.colors[i][j][2]) > (dark.colors[i][j][0] +
				    dark.colors[i][j][1] +
				    dark.colors[i][j][2] + bias))

	output.grays[i][j] = WW_GRAY_MAX;

      else
	output.grays[i][j] = WW_GRAY_MIN;
    }
}
