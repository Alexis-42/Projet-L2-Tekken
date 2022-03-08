#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/personnages.h"

void initPerso(Joueur * j, int i){
	switch(i){
		case 0:
			j->perso.nom="Pingutest";
			j->perso.taille_x=220;
			j->perso.taille_y=320;
		break;
		case 1:
			j->perso.nom="Shrektest";
			j->perso.taille_x=176;
			j->perso.taille_y=320;
		break;
	}
}
