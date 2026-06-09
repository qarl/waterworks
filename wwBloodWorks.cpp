#include "ww.h"

void wwBloodWorks::doIt(const wwMapColor &input, wwMapColor &output)
{
  locator.locateUser(input, user);

  for (int i = 0; i < 2; i++)
    {
      spigot.doIt(water);
      simulator.doIt(user, water);
    }

  render.doIt(input, water, output);
}
