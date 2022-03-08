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

#define VITESSE 10

void sauter(Joueur * joueur){
	int i, pos=joueur->position.y;
	for(i=pos; i<0; i++, joueur->position.y--);
}

void attaquer(Joueur * jAttaquant, Joueur * j2){
	jAttaquant->action=POING;

	if(checkCollisions(jAttaquant, j2)){
		j2->action=PARER;
		j2->vie-=50;
		//test_son();
	}
}

void deplacements(Joueur * j1, Joueur * j2) {
  direction(j1, j2);
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    quit = true;
    break;

  case SDL_MOUSEBUTTONDOWN:
    switch (event.button.button) {
      case SDL_BUTTON_RIGHT:
        j1->action=PARER;
        break;
      case SDL_BUTTON_LEFT:
        attaquer(j1, j2);
        break;
  }
  break;

  case SDL_MOUSEBUTTONUP:
  switch (event.button.button) {
    case SDL_BUTTON_RIGHT:
      j1->action=IDLE;
      break;
    case SDL_BUTTON_LEFT:
      j1->action=IDLE;
      break;
    }
    break;

  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_q:
      if(j1->position.x>0){
        j1->position.x -= VITESSE;
        j1->action=COURIR;
       }
      break;
    case SDLK_d:
      if(j1->position.x<ecran.w-j1->perso.taille_x){
				//if(event.key.repeat == 1)
        j1->position.x += VITESSE;
        j1->action=COURIR;

       }
      break;
    case SDLK_SPACE:
      sauter(j1);
      break;
    }
	break;

  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
      case SDLK_q:
      j1->action=IDLE;
        break;
      case SDLK_d:
      j1->action=IDLE;
        break;
      case SDLK_z:
      j1->action=IDLE;
        break;
    }
    break;
}
}
