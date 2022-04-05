/**
 * @file pause.h
 * @author Charly.P Alexis.G Léo.N
 * @brief fichier header qui possède les fonctions en relation avec le menu pause
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PAUSE_H_INCLUDED__
#define PAUSE_H_INCLUDED__
#include <SDL2/SDL.h>

/**
 * @brief fonction d'affichage du menu pause 
 * 
 */
void renderPause();

/**
 * @brief fonction qui initialise le menu pause pour pouvoir l'utiliser après sans problème
 * 
 */
void initPause();

/**
 * @brief fonction qui gère la sortie du menu pause
 * 
 * @param event structure des évenements de la souris
 * @param drip option d'affichage
 * @param ia variable qui vérifie si l'on est en joueur contre joueur ou en  joueur contre IA
 */
void selectionPause(SDL_Event event, int drip, int ia);
SDL_Rect btn1;

extern int sortie;

#endif
