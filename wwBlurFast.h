#ifndef WWBLURFAST_H
#define WWBLURFAST_H

class wwBlurFast : public wwOperatorSimple
{
 public:
  void doIt(const wwMapColor &input, wwMapColor &output);
  void doIt(const wwMapGray &input, wwMapGray &output);
};


#endif
