#include <sys/time.h>
#include "ww.h"


wwTimer::wwTimer()
{
  start();
}

void wwTimer::start()
{

  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

  start_sec  = tv.tv_sec;
  start_usec = tv.tv_usec;

  frames = 0;

  stopped = 0;
}

void wwTimer::stop()
{

  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

  stop_sec  = tv.tv_sec;
  stop_usec = tv.tv_usec;

  stopped = 1;
}


void wwTimer::newFrame()
{
  frames++;
}


float wwTimer::getFPS()
{
  long sec, usec;

  if (stopped)
    {
      sec = stop_sec;
      usec = stop_usec;
    }
  else
    {
      struct timeval tv;
      struct timezone tz;

      gettimeofday(&tv, &tz);

      sec = tv.tv_sec;
      usec = tv.tv_usec;
    }



  return (float)(frames / ((sec - start_sec) + 
			   (usec - start_usec)/1000000.0));
}



void wwTimer::printFPS()
{
  printf("%g frames per second\n", getFPS());
}

void wwTimer::printSPF()
{
  printf("%g seconds per frame\n", 1.0 / getFPS());
}
