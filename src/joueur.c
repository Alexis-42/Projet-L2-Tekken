#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"

void direction(Joueur * j1, Joueur * j2){
    if(j1->direction==gauche){ //Oui SDL c'est débile, ces deux if sont nécessaires sinon la hitbox est décalée physiquement pour le joueur regardant à gauche.
    	j1->hitbox.x+=j1->hitbox.w;
    }
    if(j2->direction==gauche){
    	j2->hitbox.x+=j2->hitbox.w;
    }
    
    j1->direction=j1->hitbox.x<j2->hitbox.x; //Direction
    j2->direction=j1->hitbox.x>j2->hitbox.x;
    
    printf("PosX J1: %d, posX hitbox J1: %d, posX rect J1: %d\n", j1->position.x, j1->hitbox.x, j1->dstrect.x); //La hitbox est décalée alors que ses coords sont identiques à celles du joueur, le calcul plus haut la décale bêtement quand le joueur regarde à gauche mais ses coords ne sont plus les mêmes que celles du joueur.
}

void hitbox(Joueur * joueur){
  SDL_Rect hitbox = {
    joueur->position.x,
    joueur->position.y,
    TAILLE_X_JOUEUR/2,
    TAILLE_Y_JOUEUR/2
  };
  joueur->hitbox=hitbox;
}

void checkPerdu(Joueur * j1, Joueur * j2){
	if(j1->vie==0)
		printf("%s a gagné !", j2->nom);
	else if(j2->vie==0)
		printf("%s a gagné !", j1->nom);
}

bool checkCollisions(Joueur * j1, Joueur * j2){
	SDL_bool collision = SDL_HasIntersection(&(j1->hitbox), &(j2->hitbox));
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
