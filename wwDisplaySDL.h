#ifndef WWDISPLAYSDL_H
#define WWDISPLAYSDL_H

#include "ww.h"
#include <SDL.h>


#define WW_ERR_SDL_MUSTLOCK (WW_ERR_SDL_GENERAL + 1)

class wwDisplaySDL
{
 public:
  wwDisplaySDL(int doublesize=-1);
  ~wwDisplaySDL();
  void display(wwMapColor &image);
 private:
  SDL_Surface *surface;
  int doublesize;
  int mirror;
};

#endif
