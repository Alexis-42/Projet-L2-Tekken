#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/jeu.h"

void renderAnimation(Joueur * joueur){
  SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->srcrect), &(joueur->dstrect), 0, 0, joueur->direction);
}

void resetAnimation(Joueur * joueur){
  SDL_Rect srcrect = {
    0, //Pas
    0,
    TAILLE_X_JOUEUR,
    TAILLE_Y_JOUEUR
  };
  SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    TAILLE_X_JOUEUR,
    TAILLE_Y_JOUEUR
  };
  joueur->srcrect=srcrect;
  joueur->dstrect=dstrect;
}

void jouerAnimation(Joueur * joueur){ //Pour freezer l'anim il faut anuller le getTick
  int posYSprite, nbFrames;
  int anim=joueur->action;

  switch (anim) {
    case COURIR: nbFrames=15; //Nombre de frames
                 posYSprite=0;
    break;
    case PARER: nbFrames=3; //Nombre de frames
                posYSprite=640;
    break;
    case POING: nbFrames=14; //Nombre de frames
                posYSprite=1310;
    break;
    case IDLE: nbFrames=1;
    		       posYSprite=0;
  }
    Uint32 seconds = SDL_GetTicks() / 30; //Fréquence (toutes les 30ms)
    Uint32 sprite = seconds % nbFrames;

  if(sprite<nbFrames){

    SDL_Rect srcrect = {
    sprite * 540, //Pas
    posYSprite,
    TAILLE_X_JOUEUR,
    TAILLE_Y_JOUEUR
  };

  SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    TAILLE_X_JOUEUR,
    TAILLE_Y_JOUEUR
  };

   joueur->srcrect=srcrect;
   joueur->dstrect=dstrect;
   } else {
   	joueur->action=IDLE;
   }
}
