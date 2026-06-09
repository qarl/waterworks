#include "ww.h"



wwInvert::wwInvert()
{
  for (int i = WW_GRAY_MIN; i <= WW_GRAY_MAX; i++)
    {
      lookup[WWREMAPGRAY(i)] = WW_GRAY_MAX - i;
    }
}
