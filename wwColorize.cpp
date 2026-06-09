#include "ww.h"



wwColorize::wwColorize(float red, float green, float blue)
{
  for (int i = WW_GRAY_MIN; i <= WW_GRAY_MAX; i++)
    {
      lookup[WWREMAPGRAY(i)][2] = (wwGray) (i * red);
      lookup[WWREMAPGRAY(i)][1] = (wwGray) (i * green);
      lookup[WWREMAPGRAY(i)][0] = (wwGray) (i * blue);
    }
}
