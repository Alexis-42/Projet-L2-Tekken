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
#include "../include/son.h"

#define VITESSE 1

bool monte=false;

typedef struct {
	Joueur * joueur;
	int anim;
} params;

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

void sauter(Joueur * joueur){
	if(joueur->sauter){
		if(monte==false && estAuSol(joueur))
			monte=true;

		if(monte==true){
			joueur->position.y-=2;
			if(estTropHaut(joueur))
          		monte=false;

		}
		if(monte==false){
			if(!estAuSol(joueur))
				joueur->position.y+=3;
			joueur->sauter=!estAuSol(joueur);
		}
	}
}

void deplacements(Joueur * j1, Joueur * j2, SDL_Event * event,int ia) {
	direction(j1, j2);
	const Uint8 * state = SDL_GetKeyboardState(NULL);
	
	switch (event->type) {
		case SDL_QUIT:
		quit = true;
		break;
		
			case SDL_KEYDOWN:
			if(j1->perso.frame==0 && j1->action==IDLE && j1->action!=MORT){
				switch (event->key.keysym.sym) {
					case SDLK_a:
						if(!(event->key.repeat)){
							j1->action=POING;
						}
						break;
					case SDLK_z:
					if(!event->key.repeat){
						j1->action=PIED;
					}
					break;
				}
				if(j2->perso.frame==0 && j2->action==IDLE){
					switch (event->key.keysym.sym) {
						case SDLK_KP_1:
							if(!(event->key.repeat)){
								j2->action=PIED;
							}
							break;
						case SDLK_KP_2:
							if(!(event->key.repeat)){
								j2->action=POING;
							}
							break;
					}
				}
			}
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
				if(!estAuSol(j1))
					j1->position.x -= VITESSE+1;
				else
					j1->position.x -= VITESSE;
				j1->action=COURIR;
			}
		}
		if (state[SDL_SCANCODE_D]){ // avance
			if((j1->hitbox.x<ecran.w-j1->perso.taille_hitbox.w) && (( (j1->hitbox.x + j1->hitbox.w < j2->hitbox.x  && j2->direction==gauche ) || (j2->hitbox.y > (j1->hitbox.y + 0.75*j1->hitbox.h)))|| j2->direction==droite)){
				if(!estAuSol(j1))
					j1->position.x += VITESSE+1;
				else
					j1->position.x += VITESSE;
				j1->action=COURIR;
			}
		}
		if (state[SDL_SCANCODE_E] && j1->action!=COURIR) { // parer
			j1->action=PARER;
		}
		if (state[SDL_SCANCODE_S] && j1->action!=COURIR) {
			j1->action=DANSE;
		}
		if (state[SDL_SCANCODE_SPACE]) { //sauter
			j1->sauter=true;
			j1->action=SAUTER;
		}
	}
	if(!ia){
	/* verif touches J2 */
		if(j2->perso.frame==0 && j2->action!=MORT){
			if (state[SDL_SCANCODE_LEFT]) {
				if(j2->hitbox.x>0 && (( (j2->hitbox.x > j1->hitbox.x  + j1->hitbox.w && j1->direction==droite ) || (j1->hitbox.y > (j2->hitbox.y + 0.75*j2->hitbox.h)))|| j1->direction==gauche)){
					if(!estAuSol(j2))
						j2->position.x -= VITESSE+1;
					else
						j2->position.x -= VITESSE;
					j2->action=COURIR;
					}
			}
			if (state[SDL_SCANCODE_RIGHT]) {
				if(j2->hitbox.x>0 && (( (j2->hitbox.x +  j2->hitbox.w < j1->hitbox.x && j1->direction==gauche ) || (j1->hitbox.y > (j2->hitbox.y + 0.75*j2->hitbox.h)))|| j1->direction==droite)){
					if(!estAuSol(j1))
						j2->position.x += VITESSE+1;
					else
						j2->position.x += VITESSE;
					j2->action=COURIR;
				}
			}
			if (state[SDL_SCANCODE_KP_3] && j2->action!=COURIR) {
				j2->action=PARER;
			}
			if (state[SDL_SCANCODE_KP_0]) {
				j2->sauter=true;
				j2->action=SAUTER;
			}
			if (state[SDL_SCANCODE_KP_5] && j2->action!=COURIR) {
				j2->action=DANSE;
			}
			
		}
	}
}