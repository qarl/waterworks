// a direct port from waterworks 1.0 - ug

#include "ww.h"
#include <stdlib.h>


#define WW_WS(x) ((x) * WW_WATER_SCALE)

wwWaterSimulator::wwWaterSimulator()
{

}


void wwWaterSimulator::doIt(const wwMapValue &user, wwMapValue &water)
{
  int x, y, count, thisw;
  char *cell;
  int xtable[WW_WATER_WIDTH * WW_WATER_HEIGHT];
  int ytable[WW_WATER_WIDTH * WW_WATER_HEIGHT];
  int tablesize;
  int d;

  /* build table of pixels */
  {
    tablesize = 0;

    for (x = 0; x < WW_WATER_WIDTH; x++)
      for (y = WW_WATER_HEIGHT -1 ; y >= 0; y--)
        {
          if (water.values[y][x])
            {
              xtable[tablesize] = x;
              ytable[tablesize] = y;
              tablesize++;
            }
          
        }
        
    /* randomize the order */
    /*    for (count = 0; count < tablesize; count++)
      {
        int tmpx, tmpy;
        int swapto;

        swapto = lrand48() % tablesize;
        tmpx = xtable[swapto];
        tmpy = ytable[swapto];
            
        xtable[swapto] = xtable[count];
        ytable[swapto] = ytable[count];

        xtable[count] = tmpx;
        ytable[count] = tmpy;
      }
    */
    d = 1;
    for (count = 0; count < tablesize; count++)
      {
        x = xtable[count];
        y = ytable[count];
        d = -d;
        {
          /* if there's water here, act on it */
          /* also, sometimes we just don't move */
          thisw = water.values[y][x];
          if ((thisw) && (count % 10) != 0)
            {
              /* if we're above the bottom row, move it */
              /* also, to prevent stagnation, sometimes we
                 disappear for no reason */
              if ((y == WW_WATER_HEIGHT - 1) || (count % 5001) == 0)
                {
                  /* fall off the bottom */
                  water.values[y][x] = 0;
                }
              else
                {
                  /* if nothing below, fall */
                  if ((!water.values[y+1][x]) &&
                      (((!user.values[WW_WS(y+1)][WW_WS(x)])) ||
                       (count % 13 == 0)))
                    {
                      water.values[y+1][x] = thisw;
                      water.values[y][x] = 0;
                    }
                  /* if nothing to the side, move there */
                  else if ((!water.values[y][x-d]) &&
                           (!user.values[WW_WS(y)][WW_WS(x-d)]))
                    {
                      water.values[y][x-d] = thisw;
                      water.values[y][x] = 0;
                    }
                  /* okay, try other side */
                  else if ((!water.values[y][x+d]) &&
                           (!user.values[WW_WS(y)][WW_WS(x+d)]))
                    {
                      water.values[y][x+d] = thisw;
                      water.values[y][x] = 0;
                    }
		  /* if the user IS here, fall slowly over him */
		  else if(((user.values[WW_WS(y)][WW_WS(x)]) &&
			   (count % 5 ==0)))
		    {
                      water.values[y+1][x] = thisw;
                      water.values[y][x] = 0;
		    }
                }
	    }
	}
      }
  }
}
