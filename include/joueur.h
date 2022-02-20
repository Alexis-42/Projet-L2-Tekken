/* complex.h */
#ifndef COMPLEX_H_INCLUDED__
#define COMPLEX_H_INCLUDED__
#include <SDL2/SDL.h>

typedef struct {
  int vie;
  char * nom;
  SDL_Rect * srcrect;
  SDL_Rect * dstrect;
} Joueur;

void initJoueur(Joueur * joueur);
#endif
