#ifndef PAUSE_H_INCLUDED__
#define PAUSE_H_INCLUDED__
#include <SDL2/SDL.h>

void renderPause();
void initPause();
void selectionPause(SDL_Event event, int drip, int ia);
SDL_Rect btn1;

extern int sortie;

#endif
