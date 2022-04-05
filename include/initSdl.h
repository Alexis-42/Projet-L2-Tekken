/**
 * @file initSdl.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header contenant les fonction en rapport avec le combat ( Round / Boucle principale de combat)
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INITSDL_H
#define INITSDL_H

#include <SDL2/SDL.h>
#include "../include/joueur.h"
/**
 * @brief Fonction qui boucle tant qu'un des deux joueurs n'a pas gagné le nombre de rounds suffisant
 * 
 * @param j1 Structure représentant le joueur 1
 * @param j2 Structure représentant le joueur 2
 * @param num_map entier représentant le numéro de la map choisie
 * @param drip entier qui vaut 1 si secret activé et 2 si mode debug activé
 * @param ia entier qui vaut 1 si le mode ia est activé ou 0 si en multi local
 */
void initSdl(Joueur * j1, Joueur * j2, int num_map, int drip, int ia) ;

#endif
