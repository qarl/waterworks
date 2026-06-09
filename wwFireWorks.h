#ifndef WWFIREWORKS_H
#define WWFIREWORKS_H

#define WW_FIRE_LENGTH 150

class wwFireWorks : public wwOperatorSimple
{
 public:
  wwFireWorks();
  ~wwFireWorks();
  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  wwLocator locator;
  wwBlurFast blur;
  wwWarp warp;

  wwMapValue user;
  wwMapGray fire;
  wwMapGray temp;

  unsigned char fire_red[WW_FIRE_LENGTH];
  unsigned char fire_green[WW_FIRE_LENGTH];
  unsigned char fire_blue[WW_FIRE_LENGTH];

  wwMapVector *flicker;
  int frame;
};


#endif
