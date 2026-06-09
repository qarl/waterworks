// a very ugly port from waterwork 1.0

#include "ww.h"
#include <math.h>


#define HEIGHT_RES 5000
#define HEIGHT_BLUR 3/4
#define HEIGHT_SCALE 256
#define HEIGHT_CUTOFF 1/60
#define HEIGHT_ROUND 2

#define COLOR_RES 100
#define COLOR_BLUR 38/48
#define COLOR_NORM 75


int height_blur1[WW_WIDTH][WW_HEIGHT];
int height_blur2[WW_WIDTH][WW_HEIGHT];
short int color_blur1[WW_WIDTH][WW_HEIGHT][3];
short int color_blur2[WW_WIDTH][WW_HEIGHT][3];

float fresnel[2*HEIGHT_RES];
float thickness[HEIGHT_RES];
int height[HEIGHT_RES];
int refract[2*HEIGHT_RES];
float specular[2*HEIGHT_RES];
float color_table[COLOR_RES*COLOR_NORM];


void wwSlimeRender::build_height_table()
{
  int i;

  for (i = 0; i < HEIGHT_RES; i++)
    {
      if (i < HEIGHT_RES * HEIGHT_CUTOFF)
	height[i] = 0;
      else
	height[i] = (int)(float)(HEIGHT_RES * 
	  pow(1.0 - pow(1.0 - (i - HEIGHT_RES * HEIGHT_CUTOFF)/
			(float)HEIGHT_RES, HEIGHT_ROUND), 1.0/HEIGHT_ROUND));
    }

}


void wwSlimeRender::build_thickness_table()
{
  int i;
  for (i = 0; i < HEIGHT_RES; i++)
    {
      thickness[i] = (pow((float)(HEIGHT_RES - i) / (float)HEIGHT_RES ,1.1));
    }

}

void wwSlimeRender::build_fresnel_table()
{
  int i;
  float slope;

  for (i = 0; i < 2*HEIGHT_RES; i++)
    {
      slope = ((float)i - HEIGHT_RES) / (float)HEIGHT_RES;
      fresnel[i] = 1.0 - pow(fabs(slope), 0.4) + 0.0;
    }
}



void wwSlimeRender::build_specular_table()
{
  int i;
  float slope;

  for (i = 0; i < 2*HEIGHT_RES; i++)
    {
      float a, slope;

      slope = (i - HEIGHT_RES) / (float)HEIGHT_RES;

      a = asin(slope);

      specular[i] =  pow(cos(a + M_PI * .008), 8000) *.9;
    }
}



void wwSlimeRender::build_refract_table()
{
  int i;
  float slope;

  for (i = 0; i < 2 * HEIGHT_RES; i++)
    {
      slope = ((float)i - HEIGHT_RES) / (float)HEIGHT_RES;
      refract[i] = (int)(-slope * 500);
    }
}


void wwSlimeRender::build_color_table()
{
  int i;

  for (i = 0; i < COLOR_RES * COLOR_NORM; i++)
    color_table[i] = pow((float)i / COLOR_RES / COLOR_NORM, 10);
}


void wwSlimeRender::make_height_blur(const wwMapValue &water)
{
  int x, y, a;

  /* put raw water bitmap into blur table */
  for (x = 0; x < WW_WATER_WIDTH; x++)
    for (y = 0; y < WW_WATER_HEIGHT; y++)
      {
	if (water.values[y][x])
	  height_blur1[x][y] = HEIGHT_RES - 1 ;
	else
	  height_blur1[x][y] = 0;
      }


  for (x = 1; x < WW_WATER_WIDTH-1; x++)
    for (y = 1; y < WW_WATER_HEIGHT-1; y++)
      {
	height_blur2[x][y] =
	  height_blur1[x+1][y+1] +
	  height_blur1[x+1][y] +
	  height_blur1[x+1][y-1] +
	  height_blur1[x][y+1] +
	  height_blur1[x][y] +
	  height_blur1[x][y] +
	  height_blur1[x][y-1] +
	  height_blur1[x-1][y+1] +
	  height_blur1[x-1][y-1] +
	  height_blur1[x-1][y+1];
      }

  for (x = 1; x < WW_WATER_WIDTH-1; x++)
    for (y = 1; y < WW_WATER_HEIGHT-1; y++)
      {
	height_blur1[x][y] =
	  height_blur2[x+1][y+1] +
	  height_blur2[x+1][y] +
	  height_blur2[x+1][y-1] +
	  height_blur2[x][y+1] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y-1] +
	  height_blur2[x-1][y+1] +
	  height_blur2[x-1][y-1] +
	  height_blur2[x-1][y+1];
      }


  for (x = 0; x < WW_WATER_WIDTH; x++)
    for (y = 0; y < WW_WATER_HEIGHT; y++)
      height_blur1[x][y] /= 128;



  for (x = 1; x < WW_WATER_WIDTH-1; x++)
    for (y = 1; y < WW_WATER_HEIGHT-1; y++)
      {
	height_blur2[x][y] =
	  height_blur1[x+1][y+1] +
	  height_blur1[x+1][y] +
	  height_blur1[x+1][y-1] +
	  height_blur1[x][y+1] +
	  height_blur1[x][y] +
	  height_blur1[x][y] +
	  height_blur1[x][y-1] +
	  height_blur1[x-1][y+1] +
	  height_blur1[x-1][y-1] +
	  height_blur1[x-1][y+1];
      }

  for (x = 1; x < WW_WATER_WIDTH-1; x++)
    for (y = 1; y < WW_WATER_HEIGHT-1; y++)
      {
	height_blur1[x][y] =
	  height_blur2[x+1][y+1] +
	  height_blur2[x+1][y] +
	  height_blur2[x+1][y-1] +
	  height_blur2[x][y+1] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y-1] +
	  height_blur2[x-1][y+1] +
	  height_blur2[x-1][y-1] +
	  height_blur2[x-1][y+1];
      }


  for (x = 0; x < WW_WATER_WIDTH; x++)
    for (y = 0; y < WW_WATER_HEIGHT; y++)
      height_blur1[x][y] /= 128;



  for (x = 2; x < WW_WIDTH-2; x++)
    for (y = 2; y < WW_HEIGHT-2; y++)
      {
	height_blur2[x][y] =
	  height_blur1[x/2+1][y/2+1] +
	  height_blur1[x/2+1][y/2] +
	  height_blur1[x/2+1][y/2-1] +
	  height_blur1[x/2][y/2+1] +
	  height_blur1[x/2][y/2] +
	  height_blur1[x/2][y/2] +
	  height_blur1[x/2][y/2-1] +
	  height_blur1[x/2-1][y/2+1] +
	  height_blur1[x/2-1][y/2-1] +
	  height_blur1[x/2-1][y/2+1];
      }

  for (x = 1; x < WW_WIDTH-1; x++)
    for (y = 1; y < WW_HEIGHT-1; y++)
      {
	height_blur1[x][y] =
	  height_blur2[x+1][y+1] +
	  height_blur2[x+1][y] +
	  height_blur2[x+1][y-1] +
	  height_blur2[x][y+1] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y-1] +
	  height_blur2[x-1][y+1] +
	  height_blur2[x-1][y-1] +
	  height_blur2[x-1][y+1];
      }


  for (x = 0; x < WW_WIDTH; x++)
    for (y = 0; y < WW_HEIGHT; y++)
      height_blur1[x][y] /= 128;


  for (x = 1; x < WW_WIDTH-1; x++)
    for (y = 1; y < WW_HEIGHT-1; y++)
      {
	height_blur2[x][y] =
	  height_blur1[x+1][y+1] +
	  height_blur1[x+1][y] +
	  height_blur1[x+1][y-1] +
	  height_blur1[x][y+1] +
	  height_blur1[x][y] +
	  height_blur1[x][y] +
	  height_blur1[x][y] +
	  height_blur1[x][y-1] +
	  height_blur1[x-1][y+1] +
	  height_blur1[x-1][y-1] +
	  height_blur1[x-1][y+1];
      }

  for (x = 1; x < WW_WIDTH-1; x++)
    for (y = 1; y < WW_HEIGHT-1; y++)
      {
	height_blur1[x][y] =
	  height_blur2[x+1][y+1] +
	  height_blur2[x+1][y] +
	  height_blur2[x+1][y-1] +
	  height_blur2[x][y+1] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y-1] +
	  height_blur2[x-1][y+1] +
	  height_blur2[x-1][y-1] +
	  height_blur2[x-1][y+1];
      }


  for (x = 0; x < WW_WIDTH; x++)
    for (y = 0; y < WW_HEIGHT; y++)
      height_blur1[x][y] /= 128;


  /*
  for (x = 1; x < WW_WIDTH-1; x++)
    for (y = 1; y < WW_HEIGHT-1; y++)
      {
	height_blur2[x][y] =
	  height_blur1[x+1][y+1] +
	  height_blur1[x+1][y] +
	  height_blur1[x+1][y-1] +
	  height_blur1[x][y+1] +
	  height_blur1[x][y] +
	  height_blur1[x][y] +
	  height_blur1[x][y] +
	  height_blur1[x][y-1] +
	  height_blur1[x-1][y+1] +
	  height_blur1[x-1][y-1] +
	  height_blur1[x-1][y+1];
      }

  for (x = 1; x < WW_WIDTH-1; x++)
    for (y = 1; y < WW_HEIGHT-1; y++)
      {
	height_blur1[x][y] =
	  height_blur2[x+1][y+1] +
	  height_blur2[x+1][y] +
	  height_blur2[x+1][y-1] +
	  height_blur2[x][y+1] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y] +
	  height_blur2[x][y-1] +
	  height_blur2[x-1][y+1] +
	  height_blur2[x-1][y-1] +
	  height_blur2[x-1][y+1];
      }


  for (x = 0; x < WW_WIDTH; x++)
    for (y = 0; y < WW_HEIGHT; y++)
      height_blur1[x][y] /= 128;

*/    
}



void make_height_blur_old(const wwMapValue &water)
{
  int x, y, a;

  /* put raw water bitmap into blur table */
  for (x = 0; x < WW_WIDTH; x++)
    for (y = 0; y < WW_HEIGHT; y++)
      {
	if (water.values[y/WW_WATER_SCALE][x/WW_WATER_SCALE])
	  height_blur1[x][y] = height_blur2[x][y] = HEIGHT_RES - 1 ;
	else
	  height_blur1[x][y] = height_blur2[x][y] = 0;
      }
  

  /* smear in Y direction */
  for (x = 0; x < WW_WIDTH; x++)
    {
      /* smear top to bottom */
      a = 0;
      for (y = 1; y < WW_HEIGHT; y++)
	{
	  a = ((int)height_blur1[x][y-1] + a) * HEIGHT_BLUR;
	  height_blur2[x][y] = height_blur1[x][y] + a;
	}

      /* smear bottom to top */
      a = 0;
      for (y = WW_HEIGHT - 2; y >= 0; y--)
	{
	  a = ((int)height_blur1[x][y+1] + a) * HEIGHT_BLUR;
	  height_blur2[x][y] += a;
	  }
    }


  /* smear in X direction */
  for (y = 0; y < WW_HEIGHT; y++)
    {
      /* smear left to right */
      a = 0;
      for (x = 1; x < WW_WIDTH; x++)
	{
	  a = ((int)height_blur2[x-1][y] + a) * HEIGHT_BLUR;
	  height_blur1[x][y] = height_blur2[x][y] + a;
	}

      /* smear right to left */
      a = 0;
      for (x = WW_WIDTH - 2; x >= 0; x--)
	{
	  a = ((int)height_blur2[x+1][y] + a) * HEIGHT_BLUR;
	  height_blur1[x][y] += a;
	  }
    }

  for (x = 0; x < WW_WIDTH; x++)
    for (y = 0; y < WW_HEIGHT; y++)
      height_blur1[x][y] /= HEIGHT_SCALE;

}




int clip256(int x)
{
  if (x > 255)
    return 255;
  else
    return x;
}


void wwSlimeRender::draw(const wwMapColor &image, const wwMapValue &water,
			 wwMapColor &output)
{
  int x, y, c;

  for (x = 0; x < WW_WIDTH -1; x++)
    for (y = 0; y < WW_HEIGHT-1 ; y++)
      {
	int h;
	int xslope, yslope;
	int rx, ry;
	
	h = height[height_blur1[x][y]];
	
	/* if there's water on this pixel, then... */
	if (h)
	  {
	    xslope = h - height[height_blur1[x+1][y]] + HEIGHT_RES;
	    yslope = h - height[height_blur1[x][y+1]] + HEIGHT_RES;

	    rx = (WW_WIDTH + x + refract[xslope]) % WW_WIDTH;
	    ry = (WW_HEIGHT + y + refract[yslope]) % WW_HEIGHT;

	    output.colors[y][x][1] =
	      clip256((int)(image.colors[ry][rx][1] *
			    fresnel[xslope] * fresnel[yslope] *
			    thickness[h]
			    + 256 * specular[xslope]*specular[yslope]));
	    output.colors[y][x][2] = 
	      (char)(256 * specular[xslope]*specular[yslope]);
	    output.colors[y][x][0] = 
	      (char)(256 * specular[xslope]*specular[yslope]);
	  }

	/* if this pixel is dry, just copy from camera */
	else

	for (c = 0; c < 3; c++)
	    output.colors[y][x][c] = 
	    clip256(image.colors[y][x][c]);
	  

      }

}


wwSlimeRender::wwSlimeRender()
{
  build_fresnel_table();
  build_thickness_table();
  build_height_table();
  build_refract_table();
  build_specular_table();
  build_color_table();
}


void wwSlimeRender::doIt(const wwMapColor &image, const wwMapValue &water,
			 wwMapColor &output)
{
  make_height_blur(water);
  draw(image, water, output);
}

