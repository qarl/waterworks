#include "ww.h"

wwGhostWorks::wwGhostWorks(int f) : timeblur(wwTimeBlur(4)), 
				    blur(wwBlurBox(15))
{
  frames = f;
  oldghost = new wwMapGray[f];

  if (!oldghost)
    throw WW_ERR_GHOST_ALLOC;
}

wwGhostWorks::~wwGhostWorks()
{
  if (oldghost)
    delete [] oldghost;
}

void wwGhostWorks::doIt(const wwMapColor &input, wwMapColor &output)
{
  locator.locateUser(input, user);

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if (1) // user.values[i][j])
	  gray.values[i][j] = (input.colors[i][j][0] +
			       input.colors[i][j][1] +
			       input.colors[i][j][2]);
	else
	  gray.values[i][j] = 256 * 3;
      }

  blur.doIt(gray, grayblurred);


  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if ((user.values[i][j]) &&
	    (gray.values[i][j] - 10 > grayblurred.values[i][j]))
	  ghost.grays[i][j] = 2;
	else
	  ghost.grays[i][j] = 0;
      }

  wwMapGray temp;
  wwBlurFast blur;

  blur.doIt(ghost, temp);
  blur.doIt(temp, ghost);



  int ghost1 = (ghostnum + frames - 60) % frames;
  int ghost2 = (ghostnum + frames - 30) % frames;
  int ghost3 = (ghostnum + frames/2) % frames;
  int ghost4 = ghostnum;

  for (int i = 0; i < WW_HEIGHT; i++)
    for (int j = 0; j < WW_WIDTH; j++)
      {
	if ((ghost.grays[i][j]) || 
	    (oldghost[ghost1].grays[i][j]) ||
	    (oldghost[ghost2].grays[i][j]) ||
	    (oldghost[ghost3].grays[i][j]) ||
	    (oldghost[ghost4].grays[i][j]))

	  {
	    output.colors[i][j][0] = 0;
	    output.colors[i][j][1] = 255;
	    output.colors[i][j][2] = 250;
	  }
	else 
	  {
	    output.colors[i][j][0] = 0;
	    output.colors[i][j][1] = 0;
	    output.colors[i][j][2] = 0;
	  }
      }

  oldghost[ghostnum] = ghost;

  ghostnum = (ghostnum+1) % frames;
  
  timeblur.doIt(output,output);
}
