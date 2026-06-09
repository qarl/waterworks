#ifndef WWNOISEPERLIN_H
#define WWNOISEPERLIN_H

class wwNoisePerlin
{
 public:
  void doIt(float amp, float hscale, float vscale, 
	    float lacunarity, int octaves, wwMapGray &output);
  void doIt(float amp, float hscale, float vscale,
	    float lacunarity, int octaves, float timescale,
	    int frames, wwMapGray *output);

 private:

};


#endif
