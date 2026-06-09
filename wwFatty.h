#ifndef WWFATTY_H
#define WWFATTY_H

#define WW_FIRE_LENGTH 150

class wwFatty : public wwOperatorSimple
{
 public:
  wwFatty();
  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  wwLocator locator;
  wwStretch stretch;
  
  wwMapGray user;
};


#endif
