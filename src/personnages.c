#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/personnages.h"

void initPerso(Joueur * j, int i){
	switch(i){
		case 0:
			j->perso.nom="Pingu";
			j->perso.taille_perso.w=310;
			j->perso.taille_perso.h=320;

			j->perso.taille_hitbox.w=140;
			j->perso.taille_hitbox.h=250;

			j->perso.hitbox_offsetX=93;
			j->perso.hitbox_offsetY=65;
		break;
		case 1:
			j->perso.nom="Shrek";
			j->perso.taille_perso.w=176;
			j->perso.taille_perso.h=320;

			j->perso.taille_hitbox.w=105;
			j->perso.taille_hitbox.h=235;

			j->perso.hitbox_offsetX=40;
			j->perso.hitbox_offsetY=57;
		break;
	}
}
