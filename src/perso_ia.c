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
#include "../include/map.h"


void jouer_animation_ia(Joueur * joueur){
SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->perso.srcrect), 
&(joueur->perso.dstrect), 0, 0, joueur->direction);

}

void render_animation_ia(Joueur * joueur){
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

  if()
  
  if(anim!=COURIR){
  if(joueur->perso.frame-1<joueur->perso.nb_frame[anim]){
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
    joueur->perso.taille_perso.w*joueur->perso.taille_perso.mult,
    joueur->perso.taille_perso.h*joueur->perso.taille_perso.mult
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
  joueur->perso.taille_perso.w*joueur->perso.taille_perso.mult,
  joueur->perso.taille_perso.h*joueur->perso.taille_perso.mult
};
 joueur->perso.srcrect=srcrect;
 joueur->perso.dstrect=dstrect;

    joueur->perso.frame++;
    joueur->perso.seconds=seconds;
}

}