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

#define VITESSE 10

void sauter(Joueur * joueur){

}

void deplacements(Joueur * joueur) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    quit = true;
    break;

  case SDL_MOUSEBUTTONDOWN:
    switch (event.button.button) {
      case SDL_BUTTON_RIGHT:
        joueur->action=PARER;
        break;
      case SDL_BUTTON_LEFT:
        joueur->action=POING;
        break;
  }
  break;

  case SDL_MOUSEBUTTONUP:
  switch (event.button.button) {
    case SDL_BUTTON_RIGHT:
      jouerAnimation(joueur, IDLE);
      break;
    case SDL_BUTTON_LEFT:
      jouerAnimation(joueur, IDLE);
      break;
    }
    break;

  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_q:
      if(joueur->posX>0)
        joueur->posX -= VITESSE;
      jouerAnimation(joueur, COURIR);
      break;
    case SDLK_d:
      if(joueur->posX<ecran.w-408)
        joueur->posX += VITESSE;
      jouerAnimation(joueur, COURIR);
      break;
    case SDLK_SPACE:
      sauter(joueur);
      break;
    }
	break;

  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
      case SDLK_q:
      jouerAnimation(joueur, IDLE);
        break;
      case SDLK_d:
      jouerAnimation(joueur, IDLE);
        break;
      case SDLK_z:
      jouerAnimation(joueur, IDLE);
        break;
      case SDLK_SPACE:
      jouerAnimation(joueur, IDLE);
        break;
    }
    break;
  }
}
