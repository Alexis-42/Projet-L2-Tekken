#include "../include/joueur.h"
#define NB_ANIMATIONS 4

#ifndef PERSO_H_INCLUDED__
#define PERSO_H_INCLUDED__

/* struc qui permet de faire le menu de selection des persos */
typedef struct {
  int w, h;
} taille;

typedef struct {
    char * nom;
    taille taille_perso;
    taille taille_hitbox;
    int hitbox_offsetX, hitbox_offsetY;
    int frame;
    Uint32 seconds;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    int nb_frame[NB_ANIMATIONS];
} Personnage;
#endif
