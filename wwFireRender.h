#ifndef WWFIRERENDER_H
#define WWFIRERENDER_H

#define WW_FIRE_LENGTH 150

class wwFireRender
{
 public:
  wwFireRender();
  ~wwFireRender();
  void doIt(const wwMapGray &fire, wwMapColor &output);

 private:
  wwGradientFilePPM gradient;

  wwNoisePerlin noise;

  wwBlurFast blur;

  wwWarp warp;
  wwMapGray temp;

  wwMapVector *flicker;
  int frame;
};


#endif
