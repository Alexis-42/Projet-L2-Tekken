#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/deplacements.h"
#include "../include/initSdl.h"
#include "../include/joueur.h"
#include "../include/animations.h"
#include "../include/jeu.h"
#include "../include/son.h"

#define VITESSE 1

typedef struct {
	Joueur * joueur;
	int anim;
} params;

void sauter(Joueur * joueur){
    Uint32 seconds = SDL_GetTicks() / 100; //Fréquence (toutes les 100ms)
	Uint32 saut = seconds % 20;
	if(estAuSol(joueur)){
		joueur->position.y-=saut;
	} else if (estTropHaut(joueur)){
		joueur->position.y+=saut;
	}
}

void deplacements(Joueur * j1, Joueur * j2, SDL_Event event) {
	direction(j1, j2);

	switch (event.type) {
		case SDL_QUIT:
		quit = true;
		break;
		
			case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				if(j1->perso.frame==0 && j1->action==IDLE){
					case SDLK_a:
						if(!(event.key.repeat)){
							j1->action=POING;
						}
						break;
				}
				if(j2->perso.frame==0 && j2->action==IDLE){
					case SDLK_KP_2:
						if(!(event.key.repeat)){
							j2->action=POING;
						}
						break;
				}
				
				if(j1->perso.frame==0 && j1->action==IDLE){
					case SDLK_z:
					if(!event.key.repeat){
						j1->action=PIED;
					}
					break;
				}
			}
			break;
		
		case SDL_KEYUP:
		switch (event.key.keysym.sym) {
			// event J1 
			if((j1->perso.frame)==0){
			case SDLK_q:
				j1->action=IDLE;
				
			case SDLK_d:
				j1->action=IDLE;
				
			case SDLK_e:
				j1->action=IDLE;
				j1->perso.frame=0;
				
			}
			// event J2 
			if((j2->perso.frame )==0){
			case SDLK_LEFT:
				j2->action=IDLE;
				
			case SDLK_RIGHT:
				j2->action=IDLE;
				
			case SDLK_KP_3:
				j2->action=IDLE;
				j2->perso.frame=0;
				
			}
		}
		break;
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	/* verif touches J1 */
	if(j1->perso.frame==0){
		if (state[SDL_SCANCODE_A]) { //recule : touche q
			if(j1->hitbox.x>0){
				j1->position.x -= VITESSE;
				j1->action=COURIR;
			}
		}
		if (state[SDL_SCANCODE_D]){ // avance
			if(j1->hitbox.x<ecran.w-j1->perso.taille_hitbox.w){
				j1->position.x += VITESSE;
				j1->action=COURIR;
			}
		}
		if (state[SDL_SCANCODE_E] && j1->action!=COURIR) { // parer
			j1->action=PARER;
		}
		if (state[SDL_SCANCODE_SPACE]) { //sauter
			j1->action=SAUTER;
		}
	/* verif touches J2 */
	}
	if(j2->perso.frame==0){
		if (state[SDL_SCANCODE_LEFT]) {
			if(j2->hitbox.x>0){
				j2->position.x -= VITESSE;
				j2->action=COURIR;
			}
		}
		if (state[SDL_SCANCODE_RIGHT]) {
			if(j2->hitbox.x<ecran.w-j2->perso.taille_hitbox.w){
				j2->position.x += VITESSE;
				j2->action=COURIR;
			}
		}
		if (state[SDL_SCANCODE_KP_3] && j2->action!=COURIR) {
			j2->action=PARER;
		}
		if (state[SDL_SCANCODE_KP_0]) {
			j2->action=SAUTER;
		}
		
	}
}
