#include <stdlib.h>
#include "ww.h"


float frand()
{
  return (float)((rand() % 100000)/100000.0);
}


wwWaterSpigotMultiRandom::wwWaterSpigotMultiRandom(int number,
					 float startchance, 
					 float stopchance)
{
  n = number;
  start = startchance;
  stop = stopchance;
  for (int i = 0; i < n; i++)
    spigots[i] == NULL;
}

wwWaterSpigotMultiRandom::~wwWaterSpigotMultiRandom()
{
  for (int i = 0; i < n; i++)
    if (spigots[i])
      delete spigots[i];

}

void wwWaterSpigotMultiRandom::doIt(wwMapValue &water)
{
  for (int i = 0; i < n; i++)
    {
      if (spigots[i] != NULL)
	{
	  spigots[i]->doIt(water);

	  if (frand() < stop)
	    {
	      delete spigots[i];
	      spigots[i] = NULL;
	    }
	}


      else
	{
	  if (frand() < start)
	    {
	      spigots[i] = new wwWaterSpigotRandom;
	    }
	}

    }


}


