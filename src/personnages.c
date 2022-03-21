#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/joueur.h"
#include "../include/personnages.h"
#include "../include/animations.h"


void initPerso(Joueur * j, int i){
	j->perso.frame=0;
	switch(i){
		case PINGU:
			j->perso.nom="Pingu";

			j->perso.nb_frame[DANSE]=46;
			j->perso.nb_frame[DEGAT]=8;
			j->perso.nb_frame[IDLE]=15;
			j->perso.nb_frame[MORT]=18;
			j->perso.nb_frame[PIED]=16;
			j->perso.nb_frame[POING]=7;
			j->perso.nb_frame[COURIR]=8;
			j->perso.nb_frame[SAUTER]=4;
			j->perso.nb_frame[PARER]=1;

			j->perso.taille_perso.w=360;
			j->perso.taille_perso.h=529;
			j->perso.taille_perso.mult=1.0;


			j->perso.taille_hitbox.w=140;
			j->perso.taille_hitbox.h=250;

			j->perso.hitbox_offsetX=93;
			j->perso.hitbox_offsetY=65;
		break;
		case SHREK:
			j->perso.nom="Shrek";

			j->perso.nb_frame[DANSE]=25;
			j->perso.nb_frame[DEGAT]=7;
			j->perso.nb_frame[IDLE]=13;
			j->perso.nb_frame[MORT]=14;
			j->perso.nb_frame[PIED]=10;
			j->perso.nb_frame[POING]=6;
			j->perso.nb_frame[COURIR]=6;
			j->perso.nb_frame[SAUTER]=4;
			j->perso.nb_frame[PARER]=1;

			j->perso.taille_perso.w=545;
			j->perso.taille_perso.h=300;
			j->perso.taille_perso.mult=1.3;

			j->perso.taille_hitbox.w=105;
			j->perso.taille_hitbox.h=235;

			j->perso.hitbox_offsetX=40;
			j->perso.hitbox_offsetY=57;
			break;
			case GOKU:
				j->perso.nom="Goku";

				j->perso.nb_frame[DANSE]=25;
				j->perso.nb_frame[DEGAT]=8;
				j->perso.nb_frame[IDLE]=15;
				j->perso.nb_frame[MORT]=14;
				j->perso.nb_frame[PIED]=10;
				j->perso.nb_frame[POING]=7;
				j->perso.nb_frame[COURIR]=8;
				j->perso.nb_frame[SAUTER]=4;
				j->perso.nb_frame[PARER]=1;

				j->perso.taille_perso.w=545;
				j->perso.taille_perso.h=300;
				j->perso.taille_perso.mult=1.3;

				j->perso.taille_hitbox.w=105;
				j->perso.taille_hitbox.h=235;

				j->perso.hitbox_offsetX=40;
				j->perso.hitbox_offsetY=70;
				break;
				case MICKEY:
					j->perso.nom="Mickey";

					j->perso.nb_frame[DANSE]=28;
					j->perso.nb_frame[DEGAT]=8;
					j->perso.nb_frame[IDLE]=15;
					j->perso.nb_frame[MORT]=14;
					j->perso.nb_frame[PIED]=8;
					j->perso.nb_frame[POING]=7;
					j->perso.nb_frame[COURIR]=7;
					j->perso.nb_frame[SAUTER]=4;
					j->perso.nb_frame[PARER]=1;

					j->perso.taille_perso.w=545;
					j->perso.taille_perso.h=300;
					j->perso.taille_perso.mult=1.3;

					j->perso.taille_hitbox.w=105;
					j->perso.taille_hitbox.h=235;

					j->perso.hitbox_offsetX=40;
					j->perso.hitbox_offsetY=57;
					break;
	}
}
