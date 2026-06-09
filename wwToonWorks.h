#ifndef WWTOONWORKS_H
#define WWTOONWORKS_H

#define WW_FIRE_LENGTH 150

class wwToonWorks : public wwOperatorSimple
{
 public:
  wwToonWorks();
  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  wwRub rub;
  wwStretch stretch;
  wwTimeBlur timeblur;
  wwMultiply multiply;
  wwLocator locator;
  wwBlurFast blurfast;
  wwBlurBox blurbox;
};



#endif
