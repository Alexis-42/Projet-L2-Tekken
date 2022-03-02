#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/jeu.h"

#define TAILLE_X_JOUEUR 408
#define TAILLE_Y_JOUEUR 672

void renderAnimation(Joueur * joueur, SDL_RendererFlip flip){
  SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->srcrect), &(joueur->dstrect), 0, NULL, flip);
}

void resetAnimation(Joueur * joueur){
  SDL_Rect srcrect = {
    0, //Pas
    0,
    520,
    640
  };
  SDL_Rect dstrect = {
    joueur->posX,
    joueur->posY,
    TAILLE_X_JOUEUR,
    TAILLE_Y_JOUEUR
  };
  joueur->srcrect=srcrect;
  joueur->dstrect=dstrect;
}

void inverserDirection(Joueur * joueur){

}

void jouerAnimation(Joueur * joueur, int anim){ //Pour freezer l'anim il faut anuller le getTick
  int posYSprite, nbFrames;
  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 30; //Fréquence (toutes les 30ms)

  switch (anim) {
    case COURIR: nbFrames=15; //Nombre de frames
                 posYSprite=0;
    break;
    case PARER: nbFrames=3; //Nombre de frames
                posYSprite=640;
    break;
    case POING: nbFrames=14; //Nombre de frames
                posYSprite=1280;
    break;
    case IDLE: nbFrames=1;
    		posYSprite=0;
  }

    Uint32 sprite = seconds % nbFrames;

    SDL_Rect srcrect = {
    sprite * 540, //Pas
    posYSprite,
    520,
    640
  };

  SDL_Rect dstrect = {
    joueur->posX,
    joueur->posY,
    TAILLE_X_JOUEUR,
    TAILLE_Y_JOUEUR
  };

   joueur->srcrect=srcrect;
   joueur->dstrect=dstrect;
}
