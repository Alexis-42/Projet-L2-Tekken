#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"
#include "../include/personnages.h"
#include "../include/map.h"

bool estTropHaut(Joueur * joueur){
  return joueur->position.y<0;
}

bool estAuSol(Joueur * joueur){
  return joueur->position.y==spawnY;
}

void direction(Joueur * j1, Joueur * j2){
    j1->direction=j1->position.x<j2->position.x; //Direction
    j2->direction=j1->position.x>j2->position.x;
}

void hitbox(Joueur * joueur){
  SDL_Rect hitbox = {
    joueur->position.x+joueur->perso.hitbox_offsetX,
    joueur->position.y+joueur->perso.hitbox_offsetY,
    joueur->perso.taille_hitbox.w,
    joueur->perso.taille_hitbox.h
  };
  joueur->hitbox=hitbox;
}

int checkPerdu(Joueur * j1, Joueur * j2){
	if(j1->vie==0)
		return 2;
	else if(j2->vie==0)
		return 1;
  return 0;
}

bool checkCollisions(Joueur * j1, Joueur * j2){
	SDL_bool collision = SDL_HasIntersection(&(j1->perso.dstrect), &(j2->hitbox));
	return collision==SDL_TRUE;
}

void initJoueur(Joueur * joueur, float posX, char * pseudo, SDL_Texture * texture, Direction direction){
  joueur->vie=100;
  joueur->action=IDLE;
  joueur->nom=pseudo;
  joueur->texture=texture;
  joueur->direction=direction;
  joueur->position.x=(posX/1280.0)*ecran.w;
  joueur->position.y=(spawnY/720.0)*ecran.h;
}
