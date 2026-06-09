#include "ww.h"

#define WW_FIRE_FLICKERFRAMES 60



wwFireWorks::wwFireWorks()
{
  // build the fire gradient
  wwFilePPM firefile;
  wwMapColor firecolor;

  firefile.load("fire.ppm", firecolor);

  for (int i = 0; i < WW_FIRE_LENGTH; i++)
    {
      fire_red[i] = firecolor.colors[0][i * WW_WIDTH / WW_FIRE_LENGTH][2];
      fire_green[i] = firecolor.colors[0][i * WW_WIDTH / WW_FIRE_LENGTH][1];
      fire_blue[i] = firecolor.colors[0][i * WW_WIDTH / WW_FIRE_LENGTH][0];
    }

  // build the flicker warp
  wwNoisePerlin noise;
  wwMapGray n[WW_FIRE_FLICKERFRAMES];
  noise.doIt(0.1, 4, 10, 0.65, 4, 0.03,  WW_FIRE_FLICKERFRAMES, n);

  wwSlope slope;
  flicker = new wwMapVector[WW_FIRE_FLICKERFRAMES];
  for (int f = 0; f < WW_FIRE_FLICKERFRAMES; f++)
    slope.doIt(n[f], flicker[f]);

  frame = 0;
}


wwFireWorks::~wwFireWorks()
{
  delete [] flicker;
}

void wwFireWorks::doIt(const wwMapColor &input, wwMapColor &output)
{
  locator.locateUser(input, user);

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if (user.values[i][j])
	  fire.grays[i][j] = WW_FIRE_LENGTH;
      }

  blur.doIt(fire, temp);
  blur.doIt(temp, fire);

  
  for (int i = 2; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	fire.grays[i-2][j] = CLIP0(fire.grays[i][j]-4);
      }

  wwMapGray fireflicker1;
  warp.doIt(fire, flicker[frame], fireflicker1);

  wwMapGray fireflicker2;
  warp.doIt(fire, flicker[(frame + WW_FIRE_FLICKERFRAMES/2) 
			  % WW_FIRE_FLICKERFRAMES], fireflicker2);


  wwMapGray fireflicker;

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      fireflicker.grays[i][j] = (fireflicker1.grays[i][j] +
				    fireflicker2.grays[i][j]) / 2;



  frame++;
  if (frame >= WW_FIRE_FLICKERFRAMES)
    frame = 0;


  blur.doIt(fireflicker, temp);
  blur.doIt(temp, fireflicker);


  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	output.colors[i][j][2] = 
	  CLIP255((input.colors[i][j][2] >> 2) + 
		  fire_red[fireflicker.grays[i][j]]);
	output.colors[i][j][1] = 
	  CLIP255((input.colors[i][j][1] >> 2) + 
		  fire_green[fireflicker.grays[i][j]]);
	output.colors[i][j][0] = 
	  CLIP255((input.colors[i][j][0] >> 2) + 
		  fire_blue[fireflicker.grays[i][j]]);
      }

}
