/**
 * @file jeu.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les extern importants ne pouvant figurer dans d'autre header
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef JEU_H
#define JEU_H

#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window * window;
SDL_Renderer * renderer;

/**
 * @brief valeur représentant la demande de quitter le jeu
 * 
 */
extern bool quit;

/**
 * @brief valeur représentant la demande de pause
 * 
 */
extern bool pause;

extern SDL_DisplayMode ecran;

#endif
