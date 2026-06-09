#include "wwDisplaySDL.h"

#include <string.h>


wwDisplaySDL::wwDisplaySDL(int d)
{

  if (d != -1)
    doublesize = d;
  
  else
    {
      if (WW_WIDTH <= 320)
	doublesize = 1;
      else
	doublesize = 0;
    }


  SDL_Init(SDL_INIT_VIDEO);

  if (doublesize)
    surface = SDL_SetVideoMode(WW_WIDTH*2, WW_HEIGHT*2, 24, 
			       SDL_SWSURFACE | SDL_FULLSCREEN); 
  else
    surface = SDL_SetVideoMode(WW_WIDTH, WW_HEIGHT, 24, 
			       SDL_SWSURFACE | SDL_FULLSCREEN); 

  if (!surface)
    {
      fprintf(stderr, "Cannot open SDL surface\n");
      throw WW_ERR_SDL_GENERAL;
    }

  SDL_ShowCursor(SDL_DISABLE);

  if(SDL_MUSTLOCK(surface))
    {
      printf("SDL_MUSTLOCK is on - not ideal\n");
      throw WW_ERR_SDL_MUSTLOCK;;
    }
}

wwDisplaySDL::~wwDisplaySDL()
{
  SDL_Quit();
}


void wwDisplaySDL::display(wwMapColor &image)
{

  if (doublesize)
    {
      for (int i = 0; i < WW_HEIGHT; i++)
	for (int j = 0; j < WW_WIDTH; j++)
	  for (int k = 0; k < 3; k++)
	    {
	      ((unsigned char *)surface->pixels)[(i*WW_WIDTH*2 + j)*3*2 + k] =
		image.colors[i][(j)][k];
	    }

      for (int i = 1; i < WW_HEIGHT-1; i++)
	for (int j = 1; j < WW_WIDTH-1; j++)
	  for (int k = 0; k < 3; k++)
	    {
	      int p = (i*WW_WIDTH*2 +j)*3*2 + k + 3;
		
	      ((unsigned char *)surface->pixels)[p] = 
		(((unsigned char *)surface->pixels)[p-3] + 
		 ((unsigned char *)surface->pixels)[p+3])/2;
	    }


      for (int i = 1; i < WW_HEIGHT-1; i++)
	for (int j = 1; j < WW_WIDTH-1; j++)
	  for (int k = 0; k < 3; k++)
	    {
	      int p = (i*WW_WIDTH*2 +j)*3*2 + k + WW_WIDTH*3*2;
		
	      ((unsigned char *)surface->pixels)[p] = 
		(((unsigned char *)surface->pixels)[p-WW_WIDTH*3*2] + 
		 ((unsigned char *)surface->pixels)[p+WW_WIDTH*3*2]) /2;
	    }


      for (int i = 1; i < WW_HEIGHT-1; i++)
	for (int j = 1; j < WW_WIDTH-1; j++)
	  for (int k = 0; k < 3; k++)
	    {
	      int p = (i*WW_WIDTH*2 +j)*3*2 + k + WW_WIDTH*3*2+3;
		
	      ((unsigned char *)surface->pixels)[p] = 
		(((unsigned char *)surface->pixels)[p-3] + 
		 ((unsigned char *)surface->pixels)[p+3]) /2;
	    }

    }


  else
    for (int i = 0; i < WW_HEIGHT; i++)
      for (int j = 0; j < WW_WIDTH; j++)
	for (int k = 0; k < 3; k++)
	  {
	    ((char *)surface->pixels)[(i*WW_WIDTH + j)*3 + k] =
	      image.colors[i][j][k];
	  }


  SDL_UpdateRect(surface, 0, 0, 0, 0);

  SDL_Event event;
  while(SDL_PollEvent(&event))
    {
      if ((event.type == SDL_KEYDOWN) || (event.type == SDL_MOUSEBUTTONDOWN))

	{
	  throw WW_QUIT;
	}
    }
}
