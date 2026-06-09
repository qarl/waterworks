#include "ww.h"

wwTimeBlur::wwTimeBlur(int factor)
{
  shift = factor;
  multiplier = (1<<factor) -1;
}

void wwTimeBlur::doIt(const wwMapColor &input, wwMapColor &output)
{
  unsigned char *in  = (unsigned char *)input.colors;
  unsigned char *out = (unsigned char *)output.colors;
  unsigned char *prev = (unsigned char *)previous.colors;

  for (int i = 0; i < WW_HEIGHT * WW_WIDTH * 3; i++)
    {
      out[i] = ((multiplier * (prev[i]) + (in[i])) >> shift);
      prev[i] = out[i];
    }
}
