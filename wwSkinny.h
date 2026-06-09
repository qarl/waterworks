#ifndef WWSKINNY_H
#define WWSKINNY_H

#define WW_FIRE_LENGTH 150

class wwSkinny : public wwOperatorSimple
{
 public:
  wwSkinny();
  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  wwLocator locator;
  wwStretch stretch;
  
  wwMapGray user;
};


#endif
