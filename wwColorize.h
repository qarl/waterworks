#ifndef WWCOLORIZE_H
#define WWCOLORIZE_H

#define WWCOLORIZE(x) ((x)-WW_GRAY_MIN)

class wwColorize : public wwRemapGrayColor
{
 public:
  wwColorize(float red=1.0, float green=1.0, float blue=1.0);
  
};


#endif
