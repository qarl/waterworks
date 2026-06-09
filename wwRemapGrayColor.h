#ifndef WWREMAPGRAYCOLOR_H
#define WWREMAPGRAYCOLOR_H

#define WWREMAPGRAYCOLOR(x) ((x)-WW_GRAY_MIN)

class wwRemapGrayColor 
{
 public:
  void doIt(const wwMapGray &input, wwMapColor &output);
  
  wwGray lookup[WW_GRAY_NUM][3];
};


#endif
