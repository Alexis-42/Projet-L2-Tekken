#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/deplacements.h"
#include "../include/initSdl.h"

void deplacementsInit(){

SDL_Event event;

// SDL_WaitEvent(&event);
SDL_PollEvent(&event);
switch (event.type){
case SDL_QUIT:
quit = true;
break;
case SDL_KEYDOWN:
switch(event.key.keysym.sym){
case SDLK_q:
x_destrec-=10;
break;
case SDLK_d:
x_destrec+=10;
break;
}

}
}
