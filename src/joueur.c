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
  return joueur->position.y>=740.0;
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

  SDL_Rect hitbox2 = {
    hitbox.x,
    hitbox.y,
    joueur->perso.taille_hitbox_coup.w,
    joueur->perso.taille_hitbox_coup.h
  };
  joueur->hitbox=hitbox;
  joueur->hitbox_coup=hitbox2;
}

void checkPerdu(Joueur * j1, Joueur * j2){
	if(j1->vie==0)
    j1->action=MORT;
	else if(j2->vie==0)
    j2->action=MORT;
}

bool checkCollisions(Joueur * j1, Joueur * j2){
	SDL_bool collision = SDL_HasIntersection(&(j1->hitbox_coup), &(j2->hitbox));
	return collision==SDL_TRUE;
}

void initJoueur(Joueur * joueur, float posX, char * pseudo, SDL_Texture * texture, Direction direction){
  joueur->vie=100;
  joueur->action=IDLE;
  joueur->nom=pseudo;
  joueur->texture=texture;
  joueur->direction=direction;
  joueur->position.x=(posX/1280.0)*ecran.w;
  joueur->position.y= ( (spawnY - ( joueur->perso.taille_perso.h * joueur->perso.taille_perso.mult ) )/1080.0)*ecran.h; // pas 720 apaprament
}
