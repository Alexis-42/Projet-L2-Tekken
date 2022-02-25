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
        jouerAnimation(PARER, joueur);
        break;
      case SDL_BUTTON_LEFT:
        jouerAnimation(POING, joueur);
        break;
  }
  break;

  case SDL_MOUSEBUTTONUP:
  switch (event.button.button) {
    case SDL_BUTTON_RIGHT:
      resetAnimation(joueur);
      break;
    case SDL_BUTTON_LEFT:
      resetAnimation(joueur);
      break;
    }
    break;

  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_q:
      joueur->posX -= VITESSE;
      jouerAnimation(COURIR, joueur);
      break;
    case SDLK_d:
      joueur->posX += VITESSE;
      jouerAnimation(COURIR, joueur);
      break;
    case SDLK_SPACE:
      sauter(joueur);
      break;
    }
	break;

  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
      case SDLK_q:
        jouerAnimation(IDLE, joueur);
        break;
      case SDLK_d:
        jouerAnimation(IDLE, joueur);
        break;
      case SDLK_z:
        jouerAnimation(IDLE, joueur);
        break;
      case SDLK_SPACE:
        jouerAnimation(IDLE, joueur);
        break;
    }
    break;
  }
}
