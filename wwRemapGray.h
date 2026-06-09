#ifndef WWREMAPGRAY_H
#define WWREMAPGRAY_H

#define WWREMAPGRAY(x) ((x)-WW_GRAY_MIN)

class wwRemapGray 
{
 public:
  void doIt(const wwMapGray &input, wwMapGray &output);
  void doIt(const wwMapColor &input, wwMapColor &output);
  
  wwGray lookup[WW_GRAY_NUM];
};


#endif
