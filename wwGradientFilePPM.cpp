#include "ww.h"

extern "C" {
#include <ppm.h>
}


wwGradientFilePPM::wwGradientFilePPM(const char *filename)
{
  FILE *f;
  pixel **pixmap;
  pixval maxval;
  int row, col;

  f = pm_openr(filename);

  if (!f)
    throw WW_ERR_GRADIENTFILEPPM_GENERAL;

  pixmap = ppm_readppm(f, &col, &row, &maxval);

  if (!pixmap)
    throw WW_ERR_GRADIENTFILEPPM_GENERAL;

  for (int i = WW_GRAY_MIN; i <= WW_GRAY_MAX; i++)
    {
      pixel p;

      p = pixmap[0][i * col / WW_GRAY_NUM];

      lookup[WWREMAPGRAY(i)][0] = PPM_GETB(p) * WW_GRAY_MAX / maxval;
      lookup[WWREMAPGRAY(i)][1] = PPM_GETG(p) * WW_GRAY_MAX / maxval;
      lookup[WWREMAPGRAY(i)][2] = PPM_GETR(p) * WW_GRAY_MAX / maxval;
      }

  ppm_freearray(pixmap, row);

  pm_close(f);
}

