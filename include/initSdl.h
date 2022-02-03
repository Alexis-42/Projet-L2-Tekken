#ifndef INITSDL_H
#define INITSDL_H

#include <stdbool.h>

#define FENETRE 0
#define FULLSCREEN 1
#define BORDERLESS 2

void initSdl();

extern bool quit;
extern SDL_Window * window;
extern SDL_Renderer * renderer;
extern SDL_Surface * image_perso;
extern SDL_Surface * image_stage;
extern SDL_Texture * texture_stage;
extern SDL_Texture * texture;

#endif
