/**
 * @file animations.c
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonction d'affichage du jeu \li Jouer animation perso \li Attaquer un joueur \li Jouer animation background
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

/**
 *  Variable représentant l'ecran ( ecran.w et .h disponible avec celle-ci )
 */
SDL_DisplayMode ecran;

/**
 * @brief Anime un joueur grâce à ses données dans la structure qui lui correspond
 * 
 * @param joueur Joueur qui va etre animé dans cette frame
 */
void renderAnimation(Joueur * joueur){
  SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->perso.srcrect), &(joueur->perso.dstrect), 0, 0, joueur->direction);
}

/**
 * @brief Fonction qui permet de voir si un joueur va mettre des dégats ( en fonction du coup donné )
 * 
 * @param jAttaquant Joueur qui attaque
 * @param j2 Joueur attaqué
 */
void attaquer(Joueur * jAttaquant, Joueur * j2){
	if(checkCollisions(jAttaquant, j2)){
		if(j2->action!=PARER){
      j2->action=DEGAT;
      j2->perso.frame = 0;
			if(jAttaquant->action==PIED)
				j2->vie-=jAttaquant->perso.dmg_pied;
			if(jAttaquant->action==POING)
				j2->vie-=jAttaquant->perso.dmg_poing;
    }
	}
}

/**
 * @brief fonction permettant de modifier les informations d'affichage du personnage pour une animation qui doit être affiché entierement et qui ne doit pas se joué en boucle
 * 
 * @param joueur structure des informations du joueur à qui l'on veut modifié ses paramètre d'affichage
 * @param seconds temps zn seconde depuis le lancement du jeu
 * @param j2 structure des informations du joueur adverse
 */
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

      if(joueur->action==PIED && j2->action==PARER && joueur->perso.frame==(joueur->perso.nb_frame[anim]/2)){
				j2->action=DEGAT;
        j2->perso.frame = 0;
    }

    if(joueur->perso.frame == joueur->perso.nb_frame[anim] ){
      joueur->perso.frame=0;
      joueur->action=IDLE;
    }
    //printf("\nframe %d de %i",joueur->perso.frame,joueur->action);
  }
}

/**
 * @brief fonction permettant de modifier les informations d'affichage du personnage pour une animation qui n'a pas à être affiché entierement et qui doit se joué en boucle tant que la touche est appuyé
 * 
 * @param joueur structure des informations du joueur à qui l'on veut modifié ses paramètre d'affichage
 * @param seconds temps zn seconde depuis le lancement du jeu
 */
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

    int posXSprite;
    if(!estAuSol(joueur) && (joueur->position.y < spawnY-(500.0/1080*ecran.h))){
      posXSprite=3;
    }else{
      posXSprite=seconds%joueur->perso.nb_frame[anim];
    }
    SDL_Rect srcrect = {
    posXSprite * 540, //Pas
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



/**
 * @brief Initialise les valeurs des rectangles afin d'animer un fond ( en mode preview ou en background )
 * 
 * @param srcBg Rectangle qui va être utilisé pour lire une partie de sprite ( chargée dans une texture )
 * @param dstBg Rectangle d'affichage sur l'écran
 * @param flag_bg @li = 1 si on veut animer un background @li = 2 si on veut animer une preview ( menu selection )
 */
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
