#include "../include/joueur.h"
#ifndef DEPL_H_INCLUDED__
#define DEPL_H_INCLUDED__

#define VITESSE 10

void sauter(Joueur * joueur);
void deplacements(Joueur * j1, Joueur * j2, SDL_Event * event,int ia, int * temps_parerJ2, int * temps_parerJ1);
int checkmort(Joueur * j1,Joueur * j2);
#endif
