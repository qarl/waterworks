#include "ww.h"


wwToonWorks::wwToonWorks() : stretch(wwStretch(2,2)), 
			     timeblur(wwTimeBlur(1)),
			     rub(wwRub(3,10)),
			     blurbox(wwBlurBox(2))
{

}



void wwToonWorks::doIt(const wwMapColor &input, wwMapColor &output)
{
  wwMapColor flow;
  // waterworks.doIt(input, flow);


  wwMapColor blur;
  timeblur.doIt(input, blur);

  wwMapGray rubbed, mask;
  rub.doIt(blur, rubbed);

  blurfast.doIt(rubbed,mask);
  blurfast.doIt(mask,rubbed);
  blurfast.doIt(rubbed,mask);
  blurfast.doIt(mask,rubbed);
  blurfast.doIt(rubbed,mask);
  blurfast.doIt(mask,rubbed);
  blurbox.doIt(rubbed, mask);

  wwMapColor blackend;
  multiply.doIt(input, mask, blackend);

  wwMapColor stretched;
  stretch.doIt(blackend, rubbed, output);
}
