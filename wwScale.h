#ifndef WWSCALE_H
#define WWSCALE_H

#define WWSCALE(x) ((x)-WW_GRAY_MIN)

class wwScale : public wwRemapGray
{
 public:
  wwScale(float scalar=0.5);
  
};


#endif
