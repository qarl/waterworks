#include "ww.h"


main()
{
  wwTimer timer;

  wwMapColor m1;
  wwMapColor m2;
  wwMapColor m3;
  wwBlurFast blur;
  wwLocator locator;
  wwMapValue v1;


  timer.start();
  for (int i = 0 ; i < 200; i++)
    {
      locator.locateUser(m1,v1);
      timer.newFrame();
    }
  
  timer.printSPF();

}
