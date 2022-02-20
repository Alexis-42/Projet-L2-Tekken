#ifndef INITSDL_H
#define INITSDL_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define FENETRE 0
#define FULLSCREEN 1
#define BORDERLESS 2

void initSdl();

extern bool quit;

#endif
