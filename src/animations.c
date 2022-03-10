#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/personnages.h"

void renderAnimation(Joueur * joueur){
  SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->perso.srcrect), &(joueur->perso.dstrect), 0, 0, joueur->direction);
}

void resetAnimation(Joueur * joueur){
  joueur->perso.frame=0;
  SDL_Rect srcrect = {
    0, //Pas
    0,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };
  SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };
  joueur->perso.srcrect=srcrect;
  joueur->perso.dstrect=dstrect;
}

void jouerAnimation(Joueur * joueur){ //Pour freezer l'anim il faut anuller le getTick
  int posYSprite;
  int anim=joueur->action;

  switch (anim) {
    case COURIR: posYSprite=0;
    break;
    case PARER: posYSprite=640;
    break;
    case POING: posYSprite=1280;
    break;
    case IDLE: posYSprite=0;
  }
  Uint32 seconds = SDL_GetTicks() / 30; //Fréquence (toutes les 30ms)

  if(anim!=COURIR){
  if(joueur->perso.frame<joueur->perso.nb_frame[anim]){
    if(joueur->perso.seconds!=seconds){

    SDL_Rect srcrect = {
    joueur->perso.frame * 540, //Pas
    posYSprite,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };

  SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };
   joueur->perso.srcrect=srcrect;
   joueur->perso.dstrect=dstrect;

      joueur->perso.frame++;
      joueur->perso.seconds=seconds;
    }
  }
} else {
  SDL_Rect srcrect = {
  (seconds%joueur->perso.nb_frame[anim]) * 540, //Pas
  posYSprite,
  joueur->perso.taille_perso.w,
  joueur->perso.taille_perso.h
};

SDL_Rect dstrect = {
  joueur->position.x,
  joueur->position.y,
  joueur->perso.taille_perso.w,
  joueur->perso.taille_perso.h
};
 joueur->perso.srcrect=srcrect;
 joueur->perso.dstrect=dstrect;

    joueur->perso.frame++;
    joueur->perso.seconds=seconds;
}
}

void jouerAnimationBackground(SDL_Rect * srcBg, SDL_Rect * dstBg){ //Pour freezer l'anim il faut anuller le getTick
  Uint32 seconds = SDL_GetTicks() / 100; //Fréquence (toutes les 30ms)
  Uint32 sprite = seconds % 8;
  printf("sprite : %d\n", sprite);

    SDL_Rect srcrect = {
    sprite * (6144/8),
    0,
    726,
    368
  };

  SDL_Rect dstrect = {
    0,
    0,
    ecran.w,
    ecran.h
  };
   *srcBg=srcrect;
   *dstBg=dstrect;
}
