#include "ww.h"


void wwOverlay::doIt(const wwMapGray &input1, 
		     const wwMapGray &input2,
		     const wwMapGray &alpha,
		      wwMapGray &output)
{

}



void wwOverlay::doIt(const wwMapColor &input1, 
		     const wwMapColor &input2,
		     const wwMapGray &alpha,
		     wwMapColor &output)
{
  invert.doIt(alpha, negalpha);

  wwMapColor front;
  multiply.doIt(input1, alpha, front);

  wwMapColor back;
  multiply.doIt(input2, negalpha, back);

  add.doIt(front, back, output);
}
