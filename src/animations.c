/**
 * @file animations.c
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonctions en relation avec les variables d'animations
 * @version 1.0
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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

SDL_DisplayMode ecran;

void renderAnimation(Joueur * joueur){
  SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->perso.srcrect), &(joueur->perso.dstrect), 0, 0, joueur->direction);
}


void attaquer(Joueur * jAttaquant, Joueur * j2){
	if(checkCollisions(jAttaquant, j2)){
		if(j2->action!=PARER){
			if(jAttaquant->action==PIED)
				j2->vie-=jAttaquant->perso.dmg_pied;
			if(jAttaquant->action==POING)
				j2->vie-=jAttaquant->perso.dmg_poing;
    }
	}
}

void jouerAnimation(Joueur * joueur,int seconds,Joueur * j2){
  int posYSprite;
  int anim=joueur->action;


  switch (anim) {
    case DANSE: return;
    break;
    case DEGAT: posYSprite=550;
    break;
    case IDLE: return;
    break;
    case MORT: posYSprite=1645;
    break;
    case PIED: posYSprite=2195;
    break;
    case POING: posYSprite=2745;
    break;
    case COURIR: return;
    break;
    case SAUTER: return;
    break;
    case PARER: return;
    break;
    //default: printf("\nanim = %d",anim);return;
  }

//printf("second du perso : %d\nsecond system : %d\n",joueur->perso.seconds,seconds);
if((joueur->perso.seconds)<seconds){
    SDL_Rect srcrect = {
    joueur->perso.frame * 540, //Pas
    posYSprite,
    joueur->perso.taille_perso.w/joueur->perso.taille_perso.mult,
    joueur->perso.taille_perso.h/joueur->perso.taille_perso.mult
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


    if((joueur->action==POING || joueur->action==PIED) && joueur->perso.frame==(joueur->perso.nb_frame[anim]/2)){
        attaquer(joueur,j2);
      }
    if(joueur->perso.frame == joueur->perso.nb_frame[anim] ){
      joueur->perso.frame=0;
      joueur->action=IDLE;
    }
    //printf("\nframe %d de %i",joueur->perso.frame,joueur->action);
  }
}


void jouerAnimationContinu(Joueur * joueur,int seconds){
  int posYSprite;
  int anim=joueur->action;

  switch (anim) {
    case DANSE: posYSprite=0;
    break;
    case DEGAT: return;
    break;
    case IDLE: posYSprite=1100;
    break;
    case MORT: return;
    break;
    case PIED: return;
    break;
    case POING: return;
    break;
    case COURIR: posYSprite=3290;
    break;
    case SAUTER: posYSprite=3865;
    break;
    case PARER: posYSprite=4395;
    break;
    default: printf("\nanim = %d",anim);return;
    break;
  }

  //Uint32 seconds = SDL_GetTicks() / 100; //Fréquence (toutes les 30ms)
  
    SDL_Rect srcrect = {
    (seconds%joueur->perso.nb_frame[anim]) * 540, //Pas
    posYSprite,
    joueur->perso.taille_perso.w/joueur->perso.taille_perso.mult,
    joueur->perso.taille_perso.h/joueur->perso.taille_perso.mult
    };

    SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
    };

    joueur->perso.srcrect=srcrect;
    joueur->perso.dstrect=dstrect;

    joueur->perso.frame=0;
}




void jouerAnimationBackground(SDL_Rect * srcBg, SDL_Rect * dstBg,int flag_bg){
  Uint32 seconds = SDL_GetTicks() / 100; //Fréquence (toutes les 100ms)
  Uint32 sprite = seconds % nbFramesMap;

    SDL_Rect srcrect;
    srcrect.y =0;
  if(flag_bg){
    srcrect.x = sprite * pas;
    srcrect.w = pas;
    srcrect.h =h_map;
  }else{
    srcrect.x = sprite * pas2;
    srcrect.w = pas2;
    srcrect.h =h_map2;
  }

  SDL_Rect dstrect = {
    0,
    0,
    ecran.w,
    ecran.h
  };
   *srcBg=srcrect;
  if(dstBg!=NULL)
   *dstBg=dstrect;
}
