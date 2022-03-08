#include "../include/joueur.h"

#ifndef PERSO_H_INCLUDED__
#define PERSO_H_INCLUDED__

/* struc qui permet de faire le menu de selection des persos */
typedef struct {
    char * nom;
    int taille_y;
    int taille_x;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
} Personnage;

#endif
