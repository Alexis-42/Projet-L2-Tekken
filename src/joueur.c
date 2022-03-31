#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"
#include "../include/personnages.h"
#include "../include/map.h"
#include "../include/options.h"

bool estTropHaut(Joueur * joueur){
  return joueur->position.y<=0;
}

bool estAuSol(Joueur * joueur){
  if(strcmp(joueur->perso.nom,"Mickey2")==0)
    return joueur->position.y>=(((spawnY-2) - (joueur->perso.taille_perso.h-150) )/1080.0)*ecran.h;
  return joueur->position.y>=(((spawnY-2) - (joueur->perso.taille_perso.h) )/1080.0)*ecran.h;
}

void direction(Joueur * j1, Joueur * j2){
    j1->direction=j1->position.x<j2->position.x; //Direction
    j2->direction=j1->position.x>j2->position.x;
}

 void hitbox(Joueur * joueur, SDL_Texture * texture,int coup){
  SDL_Rect hitbox = {
    joueur->position.x+joueur->perso.hitbox_offsetX/joueur->perso.taille_perso.mult,
    joueur->position.y+joueur->perso.hitbox_offsetY/joueur->perso.taille_perso.mult,
    joueur->perso.taille_hitbox.w,
    joueur->perso.taille_hitbox.h
  };
  SDL_Rect hitbox2;

  if(coup){
      if(joueur->direction == droite){
        hitbox2.x = hitbox.x;
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_coup.w;
        hitbox2.h = joueur->hitbox_coup.h; 
      }if(joueur->direction == gauche){
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_coup.w;
        hitbox2.x = (hitbox.x+hitbox.w)-hitbox2.w;
        hitbox2.h = joueur->hitbox_coup.h;   
      }
     joueur->hitbox_coup=hitbox2;
    }else{
      // si le joueur est tourné à droite
      if(joueur->direction == droite){
        hitbox2.x = hitbox.x;
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_pied.w;
        hitbox2.h = joueur->hitbox_pied.h;  
      }if(joueur->direction == gauche){
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_pied.w;
        hitbox2.x = (hitbox.x+hitbox.w)-hitbox2.w;
        hitbox2.h = joueur->hitbox_pied.h;  
      }
      joueur->hitbox_pied=hitbox2;
    }
  joueur->hitbox=hitbox;

  if(debug)
    SDL_RenderCopy(renderer, texture ,NULL , &hitbox2);
}

int checkPerdu(Joueur * j1, Joueur * j2){
	if(j1->vie<=0)
		return 1;
	else if(j2->vie<=0)
		return 2;
  return 0;
}

bool checkCollisions(Joueur * j1, Joueur * j2){
	SDL_bool collision = SDL_FALSE;
  //if(j1->action == POING)
  if(j1->action == PIED)
	  collision = SDL_HasIntersection(&(j1->hitbox_pied), &(j2->hitbox));
  else
    collision = SDL_HasIntersection(&(j1->hitbox_coup), &(j2->hitbox));

	return collision==SDL_TRUE;
}

void initJoueur(Joueur * joueur, float posX, SDL_Texture * texture, Direction direction){
  joueur->vie=100;
  joueur->action=IDLE;
  joueur->sauter=false;
  joueur->texture=texture;
  joueur->direction=direction;
  joueur->position.x=(posX/1280.0)*ecran.w;
  if(strcmp(joueur->perso.nom,"Mickey")==0)
    joueur->position.y= ( (spawnY - (joueur->perso.taille_perso.h-150) )/1080.0)*ecran.h;
  else
    joueur->position.y= ( (spawnY - joueur->perso.taille_perso.h )/1080.0)*ecran.h;
  joueur->perso.frame=0;
}
