#include "ww.h"



wwScale::wwScale(float scalar)
{
  for (int i = WW_GRAY_MIN; i <= WW_GRAY_MAX; i++)
    {
      lookup[WWREMAPGRAY(i)] = (wwGray) CLIP255((i * scalar));
    }
}
