#include <stdlib.h>
#include "ww.h"


#define WW_LOCATOR_THRESH 40
#define WW_LOCATOR_WARMUP 40
#define WW_LOCATOR_RESET_RATIO 0.66

wwLocator::wwLocator() : timeblur(wwTimeBlur(1))
{
  warmup = 0;
}


void fastblur(const wwMapColor &input, wwMapColor &output)
{
  output = input;

  for (int i = 1; i < WW_HEIGHT-1; i++)
    for (int j = 1; j < WW_WIDTH-1; j++)
      for (int k = 0; k < 3; k++)
	output.colors[i][j][k] = (input.colors[i][j][k] * 4+
				  input.colors[i+1][j][k] +
				  input.colors[i-1][j][k] +
				  input.colors[i][j+1][k] +
				  input.colors[i][j-1][k])/8;
}


short int difference(wwMapColor &m1, wwMapColor &m2, int i, int j)
{
  return MAX(MAX(abs(m1.colors[i][j][0] - m2.colors[i][j][0]),
		 abs(m1.colors[i][j][1] - m2.colors[i][j][1])),
	     abs(m1.colors[i][j][2] - m2.colors[i][j][2]));
}




void wwLocator::locateUser(const wwMapColor &input, wwMapValue &user)
{

  blur.doIt(input, filteredimage);

  gamma.doIt(filteredimage, filteredimage);
  timeblur.doIt(filteredimage, filteredimage);

  if (warmup < WW_LOCATOR_WARMUP)
    {
      background = filteredimage;
      warmup++;
    }


  short int differencemap[WW_HEIGHT][WW_WIDTH];

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j =0; j < WW_WIDTH; j++)
      differencemap[i][j] = difference(background, filteredimage, i, j);


  int usercount = 0;
  for (int i = 1; i < WW_HEIGHT-1; i++)
    for (int j = 1; j < WW_WIDTH-1; j++)
      {
	if ((differencemap[i-1][j-1] +
	     differencemap[i-1][j] +
	     differencemap[i-1][j+1] +
	     differencemap[i][j-1] +
	     differencemap[i][j] +
	     differencemap[i][j+1] +
	     differencemap[i+1][j-1] +
	     differencemap[i+1][j] +
	     differencemap[i+1][j+1]) > WW_LOCATOR_THRESH * 9)
	  {
	    user.values[i][j] = 255;
	    usercount++;
	  }
	else
	  user.values[i][j] = 0;
      }

  if (usercount > WW_WIDTH * WW_HEIGHT * WW_LOCATOR_RESET_RATIO)
    warmup = 0;


}


void wwLocator::doIt(const wwMapColor &input, wwMapColor &output)
{
  locateUser(input, temp);

  output = input;

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if (temp.values[i][j])
	  {
	    output.colors[i][j][2] = 255;
	  }
	else
	  {
	    output.colors[i][j][2] = 0;
	  }
      }
}


void wwLocator::doIt(const wwMapColor &input, wwMapGray &output)
{
  locateUser(input, temp);

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if (temp.values[i][j])
	  {
	    output.grays[i][j] = 255;
	  }
	else
	  {
	    output.grays[i][j] = 0;
	  }
      }
}
