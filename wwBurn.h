#ifndef WWBURN_H
#define WWBURN_H

class wwBurn
{
 public:
  wwBurn();

  void doIt(const wwMapGray &heat,
	    const wwMapGray &rate,
	    wwMapGray &burn);


 private:
  wwBlurFast blur;
  wwAddClipped add;
  wwScale scale;
  wwMultiply multiply;

  wwMapGray blurred;
  wwMapGray heatadded;


};


#endif
