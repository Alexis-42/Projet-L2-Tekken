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

#define VITESSE 7

typedef struct {
	Joueur * joueur;
	int anim;
} params;

void sauter(Joueur * joueur){
        /*if(joueur->action==SAUTER)
           if(estTropHaut(joueur))
              if(!estAuSol(joueur))
	         joueur->position.y -= 1.5;
	   else
	         joueur->position.y += 1.5;*/
}

void attaquer(Joueur * jAttaquant, Joueur * j2){
	jAttaquant->action=POING;
	if(checkCollisions(jAttaquant, j2)){
		j2->action=PARER;
		j2->vie-=20;
		test_son();
	}
}

void deplacements(Joueur * j1, Joueur * j2) {
	hitbox(j1);
	hitbox(j2);
	direction(j1, j2);
	sauter(j1);
	sauter(j2);
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
		quit = true;
		break;

		case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
			case SDL_BUTTON_RIGHT:
			resetAnimation(j1);
			j1->action=PARER;
			break;
			case SDL_BUTTON_LEFT:
			resetAnimation(j1);
			attaquer(j1, j2);
			break;
		}
		break;

		case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
			case SDL_BUTTON_RIGHT:
			resetAnimation(j1);
			j1->action=IDLE;
			break;
			case SDL_BUTTON_LEFT:
			resetAnimation(j1);
			j1->action=IDLE;
			break;
		}
		break;


		case SDL_KEYUP:
		switch (event.key.keysym.sym) {
			case SDLK_q:
			resetAnimation(j1);
			j1->action=IDLE;
			break;
			case SDLK_d:
			resetAnimation(j1);
			j1->action=IDLE;
			break;
			case SDLK_z:
			resetAnimation(j1);
			j1->action=IDLE;
			break;
		}
		break;
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A]) { //QWERTY C'EST TOTALEMENT CON
	if(j1->hitbox.x>0){
			j1->position.x -= VITESSE;
		j1->action=COURIR;
	}
}
if (state[SDL_SCANCODE_D]) {
	if(j1->hitbox.x<ecran.w-j1->perso.taille_hitbox.w){
			j1->position.x += VITESSE;
		j1->action=COURIR;
	}
}
if (state[SDL_SCANCODE_SPACE]) {
	j1->action=SAUTER;
}
if (state[SDL_SCANCODE_ESCAPE]) {
	quit=true;
}
}
