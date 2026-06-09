#include "wwCameraV4L.h"

#include <linux/videodev.h>
#include <sys/mman.h>
#include <string.h>

#define WW_V4L_DEVICE   "/dev/video0"
#define WW_V4L_NORM     VIDEO_MODE_NTSC
#define WW_V4L_CHAN     2
#define WW_V4L_PALETTE  VIDEO_PALETTE_RGB24


wwCameraV4L::wwCameraV4L(int m)
{
  mirror = m;

  int err;

  // open video device
  videofd = open(WW_V4L_DEVICE, O_RDWR);
  if (videofd < 0)
    {
      perror("V4L open");
      throw WW_ERR_V4L_GENERAL;
    }


  // switch input channel 
  struct video_channel channel;
  channel.channel = WW_V4L_CHAN;
  channel.norm = WW_V4L_NORM;
  err = ioctl(videofd, VIDIOCSCHAN, &channel);
  if (err)
    {
      perror("V4L ioctl(VIDEOCSCHAN)");
      throw WW_ERR_V4L_GENERAL;
    }


  // get image properties
  struct video_picture picture;
  err = ioctl(videofd, VIDIOCGPICT, &picture);
  if (err)
    {
      perror("V4L ioctl(VIDIOCGPICT)");
      throw WW_ERR_V4L_GENERAL;
    }

  // change image properties
  picture.depth = 24;
  picture.palette = WW_V4L_PALETTE;
  err = ioctl(videofd, VIDIOCSPICT, &picture);
  if (err)
    {
      perror("V4L ioctl(VIDIOCSPICT)");
      throw WW_ERR_V4L_GENERAL;
    }

  // get window size
  struct video_window window;
  err = ioctl(videofd, VIDIOCGWIN, &window);
  if (err)
    {
      perror("V4L ioctl(VIDIOCGWIN)");
      throw WW_ERR_V4L_GENERAL;
    }

  // set window size
  window.x = window.y = 0;
  window.width = WW_WIDTH;
  window.height = WW_HEIGHT;
  // err = ioctl(videofd, VIDIOCGWIN, &window);
  if (err)
    {
      perror("V4L ioctl(VIDIOCGWIN)");
      throw WW_ERR_V4L_GENERAL;
    }

  
  // get mmap buffer stats
  struct video_mbuf mbuf;
  err = ioctl(videofd, VIDIOCGMBUF, &mbuf);
  if (err)
    {
      perror("V4L ioctl(VIDIOCGMBUF)");
      throw WW_ERR_V4L_GENERAL;
    }
  numframes = mbuf.frames;

  // mmap the framebuffer
  mmapbuffersize = mbuf.size;
  mmapbuffer = (char *)mmap(0, mmapbuffersize,
			    PROT_READ|PROT_WRITE, MAP_SHARED,
			    videofd, 0);
  if (mmapbuffer == MAP_FAILED)
    {
      perror("V4L mmap");
      throw WW_ERR_V4L_GENERAL;
    }

  for (int i = 0; i < numframes; i++)
    framebuffer[i] = mmapbuffer + mbuf.offsets[i];

  frame = 0;

  for (int i = 0; i < numframes-1; i++)
    requestImage();
}



wwCameraV4L::~wwCameraV4L()
{
  munmap(mmapbuffer, mmapbuffersize);

  if (videofd >= 0)
    close(videofd);
}


void wwCameraV4L::requestImage()
{
  struct video_mmap map;

  map.frame  = frame;
  map.height = WW_HEIGHT;
  map.width  = WW_WIDTH;
  map.format = WW_V4L_PALETTE;

  int err = ioctl(videofd, VIDIOCMCAPTURE, &map);
  if (err)
    {
      perror("V4L ioctl(VIDIOCMCAPTURE)");
      throw WW_ERR_V4L_GENERAL;
    }

  frame = frame + 1;
  if (frame >= numframes)
    frame = 0;

}


void wwCameraV4L::waitForImage()
{
  ioctl(videofd, VIDIOCSYNC, &frame);
}



void wwCameraV4L::readImage(wwMapColor &image)
{
  requestImage();

  waitForImage();
  
  if (mirror)
    {
      unsigned char *f = (unsigned char *)framebuffer[frame];
      WW_MAP_LOOP(i,j)
	{
	  image.colors[i][WW_WIDTH - j - 1][0] =
	    f[(((i * WW_WIDTH) + j) * 3)];
	  image.colors[i][WW_WIDTH - j - 1][1] =
	    f[(((i * WW_WIDTH) + j) * 3) + 1];
	  image.colors[i][WW_WIDTH - j - 1][2] =
	    f[(((i * WW_WIDTH) + j) * 3) + 2];
	}
    }
  else
    memcpy(image.colors, framebuffer[frame], WW_WIDTH * WW_HEIGHT * 3);
}
