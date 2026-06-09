#ifndef WWFIRESIMULATOR_H
#define WWFIRESIMULATOR_H

#define WW_FIRE_LENGTH 150

class wwFireSimulator 
{
 public:
  void doIt(const wwMapGray &burn, wwMapGray &fire);

 private:
  wwBlurFast blur;
  wwMapGray temp;
};


#endif
