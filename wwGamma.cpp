#include <math.h>
#include "ww.h"

#define WW_GAMMA_DEFAULT 1.0

wwGamma::wwGamma()
{
  for (int i=0; i < 256; i++)
    gammatable[i] = (char)((float)pow((i/256.0), WW_GAMMA_DEFAULT) * 256.0);
}

void wwGamma::doIt(const wwMapColor &input, wwMapColor &output)
{
  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      for (int k = 0; k < 3; k++)
	output.colors[i][j][k] = gammatable[input.colors[i][j][k]];
}
