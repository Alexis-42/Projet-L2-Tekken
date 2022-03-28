#ifndef JEU_H
#define JEU_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define FENETRE 0
#define FULLSCREEN 1
#define BORDERLESS 2
#define MODE BORDERLESS

SDL_Window * window;
SDL_Renderer * renderer;

extern bool debug;
extern bool quit;
extern bool pause;
extern SDL_DisplayMode ecran;

#endif
