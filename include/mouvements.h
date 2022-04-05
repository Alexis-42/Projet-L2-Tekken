/**
 * @file mouvements.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier qui contient les fonctions qui permettent à un joueur de faire une action
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../include/joueur.h"
#ifndef DEPL_H_INCLUDED__
#define DEPL_H_INCLUDED__

#define VITESSE 10
/**
 * @brief fonction qui gère le déplacement vertical lors d'un saut
 * 
 * @param joueur structure du joueur
 */
void sauter(Joueur * joueur);

/**
 * @brief fonction qui vérifie les touches pressés et qui attribue aux joueurs l'action lié à la touche
 * 
 * @param j1 structure du joueur 1
 * @param j2 structure du joueur 2
 * @param event pointeur sur une structure des évenements du clavier
 * @param ia variable qui vérifie si l'on est en joueur contre joueur ou en  joueur contre IA
 * @param temps_parerJ2 temps depuis que le personnages 2 a paré
 * @param temps_parerJ1 temps depuis que le personnages 1 a paré
 */
void deplacements(Joueur * j1, Joueur * j2, SDL_Event * event,int ia, int * temps_parerJ2, int * temps_parerJ1);

/**
 * @brief fonction qui vérifie si un des personnages est mort
 * 
 * @param j1 structure du joueur 1
 * @param j2 structure du joueur 1
 * @return int retourne 1 si un des personnages est mort, 0 sinon
 */
int checkmort(Joueur * j1,Joueur * j2);
#endif
