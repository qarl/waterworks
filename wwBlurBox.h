#ifndef WWBLURBOX_H
#define WWBLURBOX_H

class wwBlurBox : public wwOperatorSimple
{
 public:

  wwBlurBox(int size=7, int bordertype=-1);
  
  ~wwBlurBox();

  void doIt(const wwMapColor &input, wwMapColor &output);
  void doIt(const wwMapValue &input, wwMapValue &output);
  void doIt(const wwMapGray &input, wwMapGray &output);


 private:
  int size;
  int bordertype;
  short *divisiontable;
};


#endif
