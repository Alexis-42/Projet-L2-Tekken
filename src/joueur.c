#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"

void checkCollisions(){
	SDL_Rect * res;
	SDL_bool SDL_IntersectRect(j1->dstrect, j2->dstrect, res);
	if(res==SDL_TRUE)
		printf("Ouin");
}

void initJoueur(Joueur * joueur, int posX, SDL_Texture * texture, Direction direction){
  joueur->vie=100;
  joueur->nom="test";
  joueur->texture=texture;
  joueur->direction=direction;
  joueur->posX=posX;
  joueur->posY=(float) 425/900*ecran.h; //425 est la valeur qui convient quand la résolution est de 900px, il faut rester proportionel avec la taille de l'écran utilisé, possiblement foireux
}
