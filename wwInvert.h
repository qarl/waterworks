#ifndef WWINVERT_H
#define WWINVERT_H

#define WWINVERT(x) ((x)-WW_GRAY_MIN)

class wwInvert : public wwRemapGray
{
 public:
  wwInvert();
  
};


#endif
