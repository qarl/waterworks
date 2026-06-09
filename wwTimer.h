#ifndef WWTIMER_H
#define WWTIMER_H

class wwTimer
{
 public:
  wwTimer();
  void start();
  void stop();
  void newFrame();
  float getFPS();
  void printFPS();
  void printSPF();

 private:
  int frames;
  long start_sec;
  long start_usec;
  long stop_sec;
  long stop_usec;
  int stopped;
};


#endif
