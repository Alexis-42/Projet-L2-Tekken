/**
 * @file personnages.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header des fonctions et strutures portants sur le joueur ( initialisation )
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../include/joueur.h"

#ifndef PERSO_H_INCLUDED__
#define PERSO_H_INCLUDED__

#define NB_ANIMATIONS 9

#define PINGU 0
#define SHREK 1
#define GOKU 2
#define MICKEY 3

/**
 * @brief struct qui permet de faire le menu de selection des persos
 * 
 */
typedef struct {
  float x, w, h, mult;
} taille;


/**
 * @brief struct qui représente un personnage
 * 
 */
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
