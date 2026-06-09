#include "ww.h"


wwStretch::wwStretch(int x, int y) : blurbox(wwBlurBox(20))
{
  xscale=x;
  yscale=y;
}

void wwStretch::doDistortion(const wwMapGray &mask)
{
  wwMapGray blur1, blur2, blur3;

  blurbox.doIt(mask,  blur1);
  blurfast.doIt(blur1, blur2);
  blurfast.doIt(blur2, blur1);
  blurfast.doIt(blur1, blur2);
  blurfast.doIt(blur2, blur3);

  slope.doIt(blur3, distortion);

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	distortion.vectors[i][j][0] /= xscale;
	distortion.vectors[i][j][1] /= yscale;
      }
}


void wwStretch::doIt(const wwMapColor &input, const wwMapGray &mask,
		     wwMapColor &output)
{
  doDistortion(mask);

  warp.doIt(input, distortion, output);
}




void wwStretch::doIt(const wwMapGray &input, const wwMapGray &mask,
		     wwMapGray &output)
{
  doDistortion(mask);

  warp.doIt(input, distortion, output);
}


