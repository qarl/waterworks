#include "ww.h"


wwSkinny::wwSkinny() : stretch(wwStretch(2,2))
{

}



void wwSkinny::doIt(const wwMapColor &input, wwMapColor &output)
{
  locator.doIt(input, user);

  stretch.doIt(input, user, output);
}
