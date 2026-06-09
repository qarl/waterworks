#include "ww.h"

wwBurn::wwBurn() : scale(wwScale(1))
{
}


void wwBurn::doIt(const wwMapGray &heat,
		  const wwMapGray &rate,
		  wwMapGray &burn)
{

  add.doIt(burn, heat, heatadded);
  blur.doIt(heatadded, blurred);
  multiply.doIt(blurred, rate, blurred);
  multiply.doIt(blurred, rate, blurred);
  multiply.doIt(blurred, rate, blurred);
  multiply.doIt(blurred, rate, blurred);
  scale.doIt(blurred, blurred);
  add.doIt(burn, blurred, burn);

}
