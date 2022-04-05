/**
 * @file ia.c
 * @author Charly.P Alexis.G Léo.N
 * @brief 
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/personnages.h"
#include "../include/options.h"
#include "../include/mouvements.h"

/**
 * @brief Fonction qui définit si l'ia peut aller à droite
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 * @return int 1 si peut parer sinon 0
 */
int peut_bouger_droite(Joueur * ia, Joueur * j1){
  return (j1->direction==droite && ( (j1->hitbox.x + j1->hitbox.w ) < ia->hitbox.x ) && ia->action==IDLE);
}

/**
 * @brief Fonction qui définit si l'ia peut aller à gauche
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 * @return int 1 si peut parer sinon 0
 */
int peut_bouger_gauche(Joueur * ia, Joueur * j1){
  return (j1->direction==gauche && ( j1->hitbox.x > ia->hitbox.x + ia->hitbox.w) && ia->action==IDLE);
}

/**
 * @brief Fonction qui définit si l'ia peut parer
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 * @return int 1 si peut parer sinon 0
 */
int peut_parer(Joueur * ia, Joueur * j1){
  return ((j1->action==POING || j1->action==PIED ) && ia->action==IDLE);
}

/**
 * @brief Fonction qui fait les mouvements et actions de l'ia 
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 */
void deplacements_ia(Joueur * ia, Joueur * j1){
    int r = rand()%1000/(difficulte*difficulte+1);
    int parer = rand()%400/(difficulte*difficulte+1);

  if( ((ia->action == COURIR || (ia->action==DANSE )) && ia->action!=DEGAT) ){
    ia->action=IDLE;
  }
  if(difficulte!=0){
 // verifier qu'il ne sort pas du terrain
  if(j1->action==DANSE && ia->action==IDLE){
    ia->action=DANSE;
  }else if(peut_bouger_droite(ia, j1) && ia->action!=DANSE){
    ia->position.x -= VITESSE;
		ia->action=COURIR;
  }else if(peut_bouger_gauche(ia, j1)&& ia->action!=DANSE){
    ia->position.x += VITESSE;
		ia->action=COURIR;
  }else if(peut_parer(ia, j1)){
    if(parer == 3)
      ia->action=PARER;
  }else if((j1->action!=POING && j1->action!=PIED ) && ia->action==PARER  && ia->action!=DEGAT){
    ia->action=IDLE;
  }else if(r==1 && ia->action==IDLE && j1->action!=PARER && ia->action!=DEGAT){
    ia->action=POING;
  }else if(r==2 && ia->action==IDLE && ia->action!=DEGAT){
    ia->action=PIED;
  }
  }
}