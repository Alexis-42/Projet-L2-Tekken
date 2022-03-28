#include "../include/joueur.h"
#ifndef DEPL_H_INCLUDED__
#define DEPL_H_INCLUDED__

void sauter(Joueur * joueur);
void deplacements(Joueur * j1, Joueur * j2, SDL_Event * event,int ia);
int checkmort(Joueur * j1,Joueur * j2);
#endif
