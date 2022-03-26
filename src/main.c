#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/initSdl.h"
#include "../include/deplacements.h"
#include "../include/menu_principal.h"

int main(int argc, char *argv[]) {
  // 1 si drip 
  if(argc>0)
    menu_principal(!strcmp(argv[1],"drip"));
  else 
    menu_principal(0);
  return 0;
}
