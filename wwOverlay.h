#ifndef WWOVERLAY_H
#define WWOVERLAY_H

class wwOverlay 
{
 public:
  void doIt(const wwMapGray &input1, const 
	    wwMapGray &input2, const wwMapGray &mask, 
	    wwMapGray &output);

  void doIt(const wwMapColor &input1, const 
	    wwMapColor &input2, const wwMapGray &mask,
	    wwMapColor &output);


 private:
  wwInvert invert;
  wwMultiply multiply;
  wwAdd add;

  wwMapGray negalpha;

};


#endif
