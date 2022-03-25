#ifndef JEU_H
#define JEU_H

#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window * window;
SDL_Renderer * renderer;

extern bool quit;
extern bool pause;
extern SDL_DisplayMode ecran;

#endif
