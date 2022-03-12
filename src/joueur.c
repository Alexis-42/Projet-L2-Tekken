#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"
#include "../include/personnages.h"

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

void checkPerdu(Joueur * j1, Joueur * j2){
/*	if(j1->vie==0)
		printf("%s a gagné !\n", j2->nom);
	else if(j2->vie==0)
		printf("%s a gagné !\n", j1->nom);*/
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
  joueur->position.x=(int)((posX/1280.0)*(float) ecran.w);
  joueur->position.y=(int)((350.0/720.0)*(float) ecran.h);
}
