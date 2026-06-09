#ifndef WWSTRETCH_H
#define WWSTRETCH_H

#define WW_FIRE_LENGTH 150

class wwStretch 
{
 public:
  wwStretch(int xscale=1, int yscale=1);
  void doIt(const wwMapColor &input, const wwMapGray &mask,
	    wwMapColor &output);
  void doIt(const wwMapGray &input, const wwMapGray &mask,
	    wwMapGray &output);

 private:
  void doDistortion(const wwMapGray &mask);

  wwBlurBox blurbox;
  wwBlurFast blurfast;
  wwSlope slope;
  wwWarp warp;
  
  wwMapVector distortion;

  int xscale, yscale;

};


#endif
