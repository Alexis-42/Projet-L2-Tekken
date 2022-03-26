#include "../include/joueur.h"
#ifndef DEPL_H_INCLUDED__
#define DEPL_H_INCLUDED__

void sauter(Joueur * joueur,SDL_Event * event, const Uint8 *state);
void deplacements(Joueur * j1, Joueur * j2, SDL_Event * event, const Uint8 * state);
#endif
