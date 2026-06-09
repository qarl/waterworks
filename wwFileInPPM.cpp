#include "ww.h"

extern "C" {
#include <ppm.h>
}


wwFileInPPM::wwFileInPPM(const char *filename)
{
  FILE *f;
  pixel **pixmap;
  pixval maxval;
  int row, col;

  f = pm_openr(filename);

  if (!f)
    throw WW_ERR_FILEPPM_GENERAL;

  pixmap = ppm_readppm(f, &col, &row, &maxval);

  if (!pixmap)
    throw WW_ERR_FILEPPM_GENERAL;


  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
        pixel p;

        p = pixmap[i * row / WW_HEIGHT][j * col / WW_WIDTH];

        cache.colors[i][j][0] = PPM_GETB(p) * 255 / maxval;
        cache.colors[i][j][1] = PPM_GETG(p) * 255 / maxval;
        cache.colors[i][j][2] = PPM_GETR(p) * 255 / maxval;
      }

  ppm_freearray(pixmap, row);

  pm_close(f);
}


void wwFileInPPM::doIt(wwMapColor &output)
{
  output = cache;
}

