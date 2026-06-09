#include "ww.h"

extern "C" {
#include <ppm.h>
}


void wwFilePPM::load(const char *filename, wwMapColor &output)
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

	output.colors[i][WW_WIDTH-j-1][0] = PPM_GETB(p) * 255 / maxval;
	output.colors[i][WW_WIDTH-j-1][1] = PPM_GETG(p) * 255 / maxval;
	output.colors[i][WW_WIDTH-j-1][2] = PPM_GETR(p) * 255 / maxval;
      }

  ppm_freearray(pixmap, row);

  pm_close(f);
}





void wwFilePPM::save(const char *filename, const wwMapColor &input)
{
  FILE *f;
  pixel **pixmap;
  pixval maxval;
  int row, col;

  row = WW_HEIGHT;
  col = WW_WIDTH;
  maxval = 255;

  pixmap=ppm_allocarray(col, row);

  f = pm_openw(filename);

  if (!f)
    throw WW_ERR_FILEPPM_GENERAL;

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	PPM_ASSIGN(pixmap[i][j],
		   input.colors[i][j][2],
		   input.colors[i][j][1],
		   input.colors[i][j][0]);
      }


  ppm_writeppm(f, pixmap, col, row, maxval, 0);

  pm_close(f);

  ppm_freearray(pixmap, row);

}
