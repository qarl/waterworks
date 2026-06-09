#ifndef WWRUB_H
#define WWRUB_H

class wwRub : public wwOperatorSimple
{
 public:
  wwRub(int lightsize=0, int darksize=10, float bias=0);
  void doIt(const wwMapColor &input, wwMapColor &output);
  void doIt(const wwMapColor &input, wwMapGray &output);

 private:
  wwBlurBox lightblur;
  wwBlurBox darkblur;

  wwMapColor light;
  wwMapColor dark;

  wwGray bias;

};


#endif
