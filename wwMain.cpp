#include <stdio.h>
#include <sys/time.h>
#include "ww.h"

extern wwMain wwMainSingleton;

wwMain::wwMain(wwOperatorSimple *o)
{
  oper = o;
}

int wwMain::main()
{
  wwCameraV4L camera;
  wwDisplaySDL display;

  wwMapColor input;
  wwMapColor output;


  timer.start();

  try
    {
      while(1)
	{
	  camera.readImage(input);

	  oper->doIt(input, output);

	  display.display(output);

	  timer.newFrame();
	}
    }


  catch(int error)
    {
      timer.printFPS();

      if (error)
	fprintf(stderr, "FATAL ERROR (%d)\n", error);

      return error;
    }
}


int main()
{
  wwMainSingleton.main();
}
