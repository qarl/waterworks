#include "ww.h"



void wwWarp::doIt(const wwMapGray &input, const wwMapVector &warp,
	  wwMapGray &output)
{
  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	int ii = CLIP0(CLIPHEIGHT(i + warp.vectors[i][j][0]));
	int jj = CLIP0(CLIPWIDTH(j + warp.vectors[i][j][1]));

	output.grays[i][j] = input.grays[ii][jj];
      }
}


void wwWarp::doIt(const wwMapColor &input, const wwMapVector &warp,
	  wwMapColor &output)
{
  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	int ii = CLIP0(CLIPHEIGHT(i + warp.vectors[i][j][0]));
	int jj = CLIP0(CLIPWIDTH(j + warp.vectors[i][j][1]));

	output.colors[i][j][0] = input.colors[ii][jj][0];
	output.colors[i][j][1] = input.colors[ii][jj][1];
	output.colors[i][j][2] = input.colors[ii][jj][2];
      }
}
