#include "../include/joueur.h"
#define NB_ANIMATIONS 9

#ifndef PERSO_H_INCLUDED__
#define PERSO_H_INCLUDED__

#define PINGU 0
#define SHREK 1
#define GOKU 2
#define MICKEY 3

/* struct qui permet de faire le menu de selection des persos */
typedef struct {
  float x, w, h, mult;
} taille;

typedef struct {
    char * nom;
    taille taille_perso;
    taille taille_hitbox;
    int hitbox_offsetX, hitbox_offsetY;
    int frame;
    int dmg_pied;
    int dmg_poing;
    Uint32 seconds;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    int nb_frame[NB_ANIMATIONS];
} Personnage;
#endif
