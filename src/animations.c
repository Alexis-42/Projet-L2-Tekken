#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/animations.h"
#include "../include/joueur.h"

void renderAnimation(SDL_Renderer * renderer, SDL_Texture * texture, Joueur * joueur){
  SDL_RenderCopy(renderer, texture, joueur->srcrect, joueur->dstrect);
}

void jouerAnimation(int anim, Joueur * joueur){
  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 60; //Fréquence (toutes les 60ms)
  Uint32 sprite;
  int nb=0;
  int x_destrec = 128;
  int y_destrec = 680;

  switch (anim) {
    case COURIR: sprite = seconds % 14; //Nombre de frames
                  nb=640;
    break;
    case POING: sprite = seconds % 14; //Nombre de frames
                  nb=640;
    break;
  }

  SDL_Rect srcrect = {
    sprite * 540, //Pas
    0,
    520,
    nb
  };
  SDL_Rect dstrect = {
    x_destrec,
    y_destrec,
    204,
    336
  };

  joueur->srcrect=&srcrect;
  joueur->dstrect=&dstrect;
}
