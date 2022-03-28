#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/personnages.h"
#define VITESSE 1

int peut_bouger_droite(Joueur * ia, Joueur * j1){
  return (j1->direction==droite && ( (j1->hitbox.x + j1->hitbox.w ) < ia->hitbox.x ) && ia->action==IDLE);
}

int peut_bouger_gauche(Joueur * ia, Joueur * j1){
  return (j1->direction==gauche && ( j1->hitbox.x > ia->hitbox.x + ia->hitbox.w) && ia->action==IDLE);
}

int peut_parer(Joueur * ia, Joueur * j1){
  return ((j1->action==POING || j1->action==PIED ) && ia->action==IDLE);
}

void deplacements_ia(Joueur * ia, Joueur * j1){
  int r = rand()%1000;
  int parer = rand()%200;
  if(ia->action == COURIR || ia->action==DANSE)
    ia->action=IDLE;
 // verifier qu'il ne sort pas du terrain
  if(j1->action==DANSE){
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
  }else if((j1->action!=POING && j1->action!=PIED ) && ia->action==PARER){
    ia->action=IDLE;
  }else if(r==1 && ia->action==IDLE){
    ia->action=POING;
  }else if(r==2 && ia->action==IDLE){
    ia->action=PIED;
  }

}