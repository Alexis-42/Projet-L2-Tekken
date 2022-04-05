/**
 * @file mouvements.c
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier qui contient les fonctions qui permettent à un joueur de faire une action
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/mouvements.h"
#include "../include/initSdl.h"
#include "../include/joueur.h"
#include "../include/animations.h"
#include "../include/jeu.h"

bool monte=false;

/**
 * @brief fonction qui vérifie si un des personnages est mort
 * 
 * @param j1 structure du joueur 1
 * @param j2 structure du joueur 1
 * @return int retourne 1 si un des personnages est mort, 0 sinon
 */
int checkmort(Joueur * j1,Joueur * j2){
	if(j1->vie<=0){
		j1->action = MORT;
		return 1;
	}else if(j2->vie<=0){
		j2->action = MORT;
		return 1;
	}
	return 0;
}

/**
 * @brief fonction qui gère le déplacement vertical lors d'un saut
 * 
 * @param joueur structure du joueur
 */
void sauter(Joueur * joueur){
	if(joueur->sauter){
		if(monte==false && estAuSol(joueur))
			monte=true;

		if(monte==true){
			joueur->position.y-=12;
			if(estTropHaut(joueur))
          		monte=false;

		}
		if(monte==false){
			if(!estAuSol(joueur))
				joueur->position.y+=24;
			joueur->sauter=!estAuSol(joueur);
		}
	}
}

/**
 * @brief fonction qui vérifie les touches pressés et qui attribue aux joueurs l'action lié à la touche
 * 
 * @param j1 structure du joueur 1
 * @param j2 structure du joueur 2
 * @param event pointeur sur une structure des évenements du clavier
 * @param ia variable qui vérifie si l'on est en joueur contre joueur ou en  joueur contre IA
 * @param temps_parerJ2 temps depuis que le personnages 2 a paré
 * @param temps_parerJ1 temps depuis que le personnages 1 a paré
 */
void deplacements(Joueur * j1, Joueur * j2, SDL_Event * event,int ia, int * temps_parerJ2, int * temps_parerJ1) {
	direction(j1, j2);
	const Uint8 * state = SDL_GetKeyboardState(NULL);
	switch (event->type) {
		case SDL_QUIT:
		quit = true;
		break;
		
		case SDL_KEYUP:
		if(j1->perso.frame==0 && j1->action!=MORT){
			switch (event->key.keysym.sym) {
			// event J1 
				case SDLK_q:
					j1->action=IDLE;
					break;
				case SDLK_d:
					j1->action=IDLE;
					break;
				case SDLK_e:
					j1->action=IDLE;
					j1->perso.frame=0;	
					break;
				case SDLK_s:
					j1->action=IDLE;
					j1->perso.frame=0;	
					break;
			}
		}
		if(!ia){
			// event J2 
			if(j2->perso.frame==0 && j2->action!=MORT){
				switch (event->key.keysym.sym) {
					case SDLK_LEFT:
						j2->action=IDLE;
						break;
					case SDLK_RIGHT:
						j2->action=IDLE;
						break;
					case SDLK_KP_3:
						j2->action=IDLE;
						j2->perso.frame=0;	
						break;		
					case SDLK_KP_5:
						j2->action=IDLE;
						j2->perso.frame=0;	
						break;	
				}
			}
			break;
		}
	}

	/* verif touches J1 */
	if(j1->perso.frame==0 && j1->action!=MORT){
		if (state[SDL_SCANCODE_A] ) { //recule : touche q
			if(j1->hitbox.x>0 && (( (j1->hitbox.x > j2->hitbox.x  + j2->hitbox.w && j2->direction==droite ) || (j2->hitbox.y > (j1->hitbox.y + 0.75*j1->hitbox.h)))|| j2->direction==gauche)){
				if(estAuSol(j1)){
					j1->position.x -= VITESSE;
					j1->action=COURIR;

				}else
					j1->position.x -= VITESSE+1;
			}
		}
		if (state[SDL_SCANCODE_D]){ // avance
			if((j1->hitbox.x<ecran.w-j1->hitbox.w) && (( (j1->hitbox.x + j1->hitbox.w < j2->hitbox.x  && j2->direction==gauche ) || (j2->hitbox.y > (j1->hitbox.y + 0.75*j1->hitbox.h)))|| j2->direction==droite)){
				if(estAuSol(j1)){
					j1->position.x += VITESSE;
					j1->action=COURIR;
				}else
					j1->position.x += VITESSE+1;
				
			}
		}
		if(state[SDL_SCANCODE_E] && j1->action!=COURIR && (SDL_GetTicks() - *temps_parerJ1)>3000) {
			j1->action=PARER;
			*temps_parerJ1=SDL_GetTicks();

		}
		if (state[SDL_SCANCODE_S] && j1->action!=COURIR) {
			j1->action=DANSE;
		}
		if (state[SDL_SCANCODE_SPACE]) { //sauter
			j1->sauter=true;
			j1->action=SAUTER;
		}
		if(state[SDL_SCANCODE_Q]) {
			if(event->key.keysym.sym==SDLK_a) {
				if(!(event->key.repeat)){
						j1->action=POING;
				}
			}
		}
		if(state[SDL_SCANCODE_W]) {
			if(event->key.keysym.sym==SDLK_z) {
				if(!(event->key.repeat)){
					j1->action=PIED;
				}
			}
		}
	}
	if(!ia){
	/* verif touches J2 */
		if(j2->perso.frame==0 && j2->action!=MORT){
			if (state[SDL_SCANCODE_LEFT]) {
				if(j2->hitbox.x>0 && (( (j2->hitbox.x > j1->hitbox.x  + j1->hitbox.w && j1->direction==droite ) || (j1->hitbox.y >= (j2->hitbox.y + 0.75*j2->hitbox.h)))|| j1->direction==gauche)){
					if(estAuSol(j2)){
						j2->position.x -= VITESSE;
						j2->action=COURIR;
					}else
						j2->position.x -= VITESSE+1;
					
					}
			}
			if (state[SDL_SCANCODE_RIGHT]) {
				if((j2->hitbox.x<ecran.w-j2->hitbox.w) && (( (j2->hitbox.x + j2->hitbox.w < j1->hitbox.x  && j1->direction==gauche ) || (j1->hitbox.y > (j1->hitbox.y + 0.75*j2->hitbox.h)))|| j1->direction==droite)){
					if(estAuSol(j2)){
						j2->position.x += VITESSE;
						j2->action=COURIR;
					}else
						j2->position.x += VITESSE+1;
					
				}
			}
			if (state[SDL_SCANCODE_KP_3] && j2->action!=COURIR && (SDL_GetTicks() - *temps_parerJ2)>3000) {
				j2->action=PARER;
				//printf("\n\ntemps avant : %d",*temps_parerJ2);
				*temps_parerJ2 = SDL_GetTicks();
				//printf("  temps apres : %d\n\n",*temps_parerJ2);
			}
			if (state[SDL_SCANCODE_KP_0]) {
				j2->sauter=true;
				j2->action=SAUTER;
			}
			if (state[SDL_SCANCODE_KP_5] && j2->action!=COURIR) {
				j2->action=DANSE;
			}
			if (state[SDL_SCANCODE_KP_1]){
				if(event->key.keysym.sym==SDLK_KP_1) {
					if(!(event->key.repeat)){
						j2->action=PIED;
					}
				}
			}
			if (state[SDL_SCANCODE_KP_2]){
				if(event->key.keysym.sym==SDLK_KP_2) {
					if(!(event->key.repeat)){
						j2->action=POING;
					}
				}
			}
		}
	}
	if(estAuSol(j1) && j1->action==SAUTER){
		j1->action=IDLE;
		j1->perso.frame=0;
	}if(estAuSol(j2) && j2->action==SAUTER){
		j2->action=IDLE;
		j2->perso.frame=0;
	}
	
	if(j1->sauter){
		j1->action=SAUTER;
	}if(j2->sauter){
		j2->action=SAUTER;
	}

}