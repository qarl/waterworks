#ifndef WWLOCATOR_H
#define WWLOCATOR_H

class wwLocator : public wwOperatorSimple
{
 public:
  wwLocator();
  void doIt(const wwMapColor &image, wwMapColor &output);
  void locateUser(const wwMapColor &image, wwMapValue &user);
  void doIt(const wwMapColor &image, wwMapGray &output);

 private:
  wwGamma gamma;
  wwBlurFast blur;
  wwTimeBlur timeblur;

  wwMapColor background;
  wwMapColor filteredimage;
  wwMapValue temp;

  int warmup;

};

#endif

