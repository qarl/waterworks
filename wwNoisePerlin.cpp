#include <math.h>
#include "ww.h"

extern "C" {
#include "perlin.h"
}



static float perlinfract(float x, float y, float z, 
			 float lacunarity, int octaves)
{
  float value = 0;
  float amp = 1;

  for (int i = 0; i < octaves; i++)
    {
      float vec[3];

      vec[0] = x;
      vec[1] = y;
      vec[2] = z;

      value += amp * noise3(vec);

      x *= 2.0;
      y *= 2.0;
      z *= 2.0;

      amp /= 2.0 * lacunarity;
    }

  return value;
}



void wwNoisePerlin::doIt(float amp, float hscale, float vscale,
			 float lacunarity, 
			 int octaves, wwMapGray &output)
{
  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	float value = amp * perlinfract((float)i * hscale/WW_WIDTH, 
					(float)j * vscale/WW_WIDTH, 0,
					lacunarity, octaves);

	output.grays[i][j] = 
	  (unsigned char)CLIP0(CLIP255(((value+1.0)/2.0) * 256));
      }

}

void wwNoisePerlin::doIt(float amp, float hscale, float vscale,
			 float lacunarity, 
			 int octaves, float timescale, int frames,
			 wwMapGray *output)
{
  for (int f = 0; f < frames; f++)
    for (int i = 0; i < WW_HEIGHT; i++)
      for (int j = 0; j < WW_WIDTH; j++)
	{
	  float value = 0;

	  for (int of = 0; of < 4; of++)
	    {
	      int nf = (f + of * frames/4) % frames;

	      value += amp * (((-cos((float)nf/frames*2.0*M_PI)+1.0)/2.0 * 
			       perlinfract((float)i * hscale / WW_HEIGHT, 
					   (float)j * vscale / WW_WIDTH,
					   (float)nf * timescale + 
					   of * frames,
					   lacunarity, octaves)));
	    }
	  
	  output[f].grays[i][j] = 
	    (unsigned char)CLIP0(CLIP255(((value+1.0)/2.0) * 256));
      }

}
