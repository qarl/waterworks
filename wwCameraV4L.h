#ifndef WWCAMERAV4L_H
#define WWCAMERAV4L_H

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ww.h"


class wwCameraV4L
{
 public:
  wwCameraV4L(int mirror=1);
  ~wwCameraV4L();
  
  void requestImage();
  void waitForImage();
  void readImage(wwMapColor &image);

 private:
  int mirror;
  int videofd;
  int frame;
  int numframes;
  char *framebuffer[1024];
  char *mmapbuffer;
  int mmapbuffersize;
};

#endif
