/**
 * @file ia.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header des fonctions qui régissent les mouvements et actions de l'intelligence artificielle
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Fonction qui définit si l'ia peut parer
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 * @return int 1 si peut parer sinon 0
 */
int peut_parer(Joueur * ia, Joueur * j1);

/**
 * @brief Fonction qui définit si l'ia peut aller à gauche
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 * @return int 1 si peut parer sinon 0
 */
int peut_bouger_gauche(Joueur * ia, Joueur * j1);

/**
 * @brief Fonction qui définit si l'ia peut aller à droite
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 * @return int 1 si peut parer sinon 0
 */
int peut_bouger_droite(Joueur * ia, Joueur * j1);

/**
 * @brief Fonction qui fait les mouvements et actions de l'ia 
 * 
 * @param ia Structure Joueur de l'ia
 * @param j1 Structure Joueur du joueur
 */
void deplacements_ia(Joueur * ia, Joueur * j1);