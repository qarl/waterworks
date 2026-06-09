#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "ww.h"


#define DELTHRESH 40
#define CHANGETHRESH 0.1


int main()
{
  wwCameraV4L camera;

  wwFilePPM file;

  wwMapColor output;
  wwMapColor lastoutput;

  while(1)
    {

      camera.readImage(output);

      int counter = 0;

      for (int i = 0; i < WW_HEIGHT; i++)
	for (int j = 0; j < WW_WIDTH; j++)
	  if ((abs((int)output.colors[i][j][0] - 
		   lastoutput.colors[i][j][0]) +
	       abs((int)output.colors[i][j][1] - 
		   lastoutput.colors[i][j][1]) +
	       abs((int)output.colors[i][j][2] - 
		   lastoutput.colors[i][j][2])) > DELTHRESH)
	    counter++;


      if ((float)counter/WW_HEIGHT/WW_WIDTH > CHANGETHRESH)
	{

	  char buff[1024];

	  sprintf(buff, "%d.ppm", time(NULL));

	  file.save(buff, output);
	  lastoutput = output;

	}


      sleep(20);
    }

}
