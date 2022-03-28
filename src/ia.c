#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/personnages.h"
#define VITESSE 1

void deplacements_ia(Joueur * ia, Joueur * j1){
  int r = rand()%1000;
  if(ia->action == COURIR)
    ia->action=IDLE;
 // verifier qu'il ne sort pas du terrain
  if(j1->direction==droite && ( (j1->hitbox.x) < ia->position.x) && ia->action==IDLE){
    ia->position.x -= VITESSE;
		ia->action=COURIR;
  }else if(j1->direction==gauche && ( j1->hitbox.x > ia->position.x) && ia->action==IDLE){
    ia->position.x += VITESSE;
		ia->action=COURIR;
  }else if(r==1 && ia->action==IDLE){
    ia->action=POING;
  }else if(r==2 && ia->action==IDLE){
    ia->action=PIED;
  }

}