#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/jeu.h"

#define TAILLE_X_JOUEUR 408
#define TAILLE_Y_JOUEUR 672

void renderAnimation(Joueur * joueur){
  SDL_RenderCopy(renderer, (joueur->texture), &(joueur->srcrect), &(joueur->dstrect));
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
  renderAnimation(joueur);
}

void jouerAnimation(int anim, Joueur * joueur){
  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 30; //Fréquence (toutes les 60ms)
  Uint32 sprite;
  int posYSprite, nbFrames;
  int i;

  switch (anim) {
    case COURIR: nbFrames=15; //Nombre de frames
                 posYSprite=0;
    break;
    case PARER: nbFrames=3; //Nombre de frames
                posYSprite=680;
    break;
    case POING: nbFrames=14; //Nombre de frames
                posYSprite=1280;
    break;
  }
  sprite = seconds % nbFrames;
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

  for(i=0; i<nbFrames; i++){
    joueur->srcrect=srcrect;
    joueur->dstrect=dstrect;
    renderAnimation(joueur);
  }
}
