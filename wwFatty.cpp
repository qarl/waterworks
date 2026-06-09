#include "ww.h"


wwFatty::wwFatty() : stretch(wwStretch(-2,-2))
{

}



void wwFatty::doIt(const wwMapColor &input, wwMapColor &output)
{
  locator.doIt(input, user);

  stretch.doIt(input, user, output);
}
