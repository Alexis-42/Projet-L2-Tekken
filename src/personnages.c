#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/joueur.h"
#include "../include/personnages.h"
#include "../include/animations.h"


void initPerso(Joueur * j, int i){
	j->perso.frame=0;
	j->perso.seconds=0;
	switch(i){
		case PINGU:
			// perso fait 180px en wide
			j->perso.nom="Pingu";
			j->perso.dmg_pied=15;
			j->perso.dmg_poing=10;

			j->perso.nb_frame[DANSE]=21;
			j->perso.nb_frame[DEGAT]=8;
			j->perso.nb_frame[IDLE]=15;
			j->perso.nb_frame[MORT]=18;
			j->perso.nb_frame[PIED]=16;
			j->perso.nb_frame[POING]=7;
			j->perso.nb_frame[COURIR]=8;
			j->perso.nb_frame[SAUTER]=4;
			j->perso.nb_frame[PARER]=1;

			j->perso.taille_perso.mult=2;
			j->perso.taille_perso.w=470.0*j->perso.taille_perso.mult;
			j->perso.taille_perso.h=300.0*j->perso.taille_perso.mult;


			j->perso.taille_hitbox.w=180*j->perso.taille_perso.mult;
			j->perso.taille_hitbox.h=j->perso.taille_perso.h*j->perso.taille_perso.mult;

			j->hitbox_pied.y=j->hitbox.y;
			j->hitbox_coup.x=j->perso.taille_hitbox.w-15*j->perso.taille_perso.mult;
			j->hitbox_coup.w=j->perso.taille_hitbox.w+30*j->perso.taille_perso.mult;
			j->hitbox_coup.h=j->perso.taille_perso.h;

			j->hitbox_pied.x=j->hitbox.y;
			j->hitbox_pied.x=j->perso.taille_hitbox.w-15*j->perso.taille_perso.mult;
			j->hitbox_pied.w=j->perso.taille_hitbox.w+30*j->perso.taille_perso.mult;
			j->hitbox_pied.h=j->perso.taille_perso.h;

			j->perso.hitbox_offsetX=((j->perso.taille_perso.w-j->perso.taille_hitbox.w)/2.0)*j->perso.taille_perso.mult;
			j->perso.hitbox_offsetY=65*j->perso.taille_perso.mult;
		break;
		case SHREK:
			// perso fait 150px en wide
			j->perso.nom="Shrek";
			j->perso.dmg_pied=15;
			j->perso.dmg_poing=5;

			j->perso.nb_frame[DANSE]=25;
			j->perso.nb_frame[DEGAT]=7;
			j->perso.nb_frame[IDLE]=13;
			j->perso.nb_frame[MORT]=14;
			j->perso.nb_frame[PIED]=10;
			j->perso.nb_frame[POING]=6;
			j->perso.nb_frame[COURIR]=6;
			j->perso.nb_frame[SAUTER]=4;
			j->perso.nb_frame[PARER]=1;

			j->perso.taille_perso.mult=1.0;
			j->perso.taille_perso.w=545*j->perso.taille_perso.mult;
			j->perso.taille_perso.h=300*j->perso.taille_perso.mult;

			j->perso.taille_hitbox.w=180;
			j->perso.taille_hitbox.h=j->perso.taille_perso.h;

			j->hitbox_pied.y=j->hitbox.y;
			j->hitbox_coup.x=j->perso.taille_hitbox.w-15*j->perso.taille_perso.mult;
			j->hitbox_coup.w=j->perso.taille_hitbox.w+30*j->perso.taille_perso.mult;
			j->hitbox_coup.h=j->perso.taille_perso.h;

			j->hitbox_pied.x=j->hitbox.y;
			j->hitbox_pied.x=j->perso.taille_hitbox.w-35;
			j->hitbox_pied.w=j->perso.taille_hitbox.w+70;
			j->hitbox_pied.h=j->perso.taille_perso.h;

			j->perso.hitbox_offsetX=((j->perso.taille_perso.w-j->perso.taille_hitbox.w)/2.0)*j->perso.taille_perso.mult;
			j->perso.hitbox_offsetY=57*j->perso.taille_perso.mult;
			break;
			case GOKU:
				j->perso.nom="Goku";
				j->perso.dmg_pied=7;
				j->perso.dmg_poing=10;

				j->perso.nb_frame[DANSE]=25;
				j->perso.nb_frame[DEGAT]=8;
				j->perso.nb_frame[IDLE]=15;
				j->perso.nb_frame[MORT]=14;
				j->perso.nb_frame[PIED]=10;
				j->perso.nb_frame[POING]=7;
				j->perso.nb_frame[COURIR]=8;
				j->perso.nb_frame[SAUTER]=4;
				j->perso.nb_frame[PARER]=1;

				j->perso.taille_perso.mult=1.75;
				j->perso.taille_perso.w=554.4 * j->perso.taille_perso.mult;
				j->perso.taille_perso.h=300 * j->perso.taille_perso.mult;
				

				j->perso.taille_hitbox.w=190 * j->perso.taille_perso.mult;
				j->perso.taille_hitbox.h=j->perso.taille_perso.h;

				j->hitbox_pied.y=j->hitbox.y;
				j->hitbox_coup.x=j->perso.taille_hitbox.w-15*j->perso.taille_perso.mult;
				j->hitbox_coup.w=j->perso.taille_hitbox.w+30*j->perso.taille_perso.mult;
				j->hitbox_coup.h=j->perso.taille_perso.h;

				j->hitbox_pied.x=j->hitbox.y;
				j->hitbox_pied.x=j->perso.taille_hitbox.w-65*j->perso.taille_perso.mult;
				j->hitbox_pied.w=j->perso.taille_hitbox.w+130*j->perso.taille_perso.mult;
				j->hitbox_pied.h=j->perso.taille_perso.h;

				j->perso.hitbox_offsetX=((j->perso.taille_perso.w-j->perso.taille_hitbox.w)/2.0)*j->perso.taille_perso.mult;
				j->perso.hitbox_offsetY=70*j->perso.taille_perso.mult;
				break;
				case MICKEY:
					j->perso.nom="Mickey";
					j->perso.dmg_pied=10;
					j->perso.dmg_poing=5;

					j->perso.nb_frame[DANSE]=28;
					j->perso.nb_frame[DEGAT]=8;
					j->perso.nb_frame[IDLE]=15;
					j->perso.nb_frame[MORT]=14;
					j->perso.nb_frame[PIED]=8;
					j->perso.nb_frame[POING]=7;
					j->perso.nb_frame[COURIR]=7;
					j->perso.nb_frame[SAUTER]=4;
					j->perso.nb_frame[PARER]=1;

					j->perso.taille_perso.mult=1.0;
					j->perso.taille_perso.w=546.4* j->perso.taille_perso.mult;
					j->perso.taille_perso.h=300* j->perso.taille_perso.mult;
					

					j->perso.taille_hitbox.w=136.6;
					j->perso.taille_hitbox.h=j->perso.taille_perso.h;

					j->hitbox_pied.y=j->hitbox.y;
					j->hitbox_coup.x=j->perso.taille_hitbox.w-15*j->perso.taille_perso.mult;
					j->hitbox_coup.w=j->perso.taille_hitbox.w+30*j->perso.taille_perso.mult;
					j->hitbox_coup.h=j->perso.taille_perso.h;

					j->hitbox_pied.y=j->hitbox.y;
					j->hitbox_pied.x=j->perso.taille_hitbox.w-60*j->perso.taille_perso.mult;
					j->hitbox_pied.w=j->perso.taille_hitbox.w+120*j->perso.taille_perso.mult;
					j->hitbox_pied.h=j->perso.taille_perso.h;

					j->perso.hitbox_offsetX=((j->perso.taille_perso.w-j->perso.taille_hitbox.w)/2.0)*j->perso.taille_perso.mult;
					j->perso.hitbox_offsetY=57*j->perso.taille_perso.mult;
					break;
	}
}
