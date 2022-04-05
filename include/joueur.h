/**
 * @file joueur.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header contenant les fonctions à propos des joueurs ( test / initialisation / affichage hitbox)
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/* complex.h */
#ifndef COMPLEX_H_INCLUDED__
#define COMPLEX_H_INCLUDED__
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/personnages.h"

typedef enum {gauche, droite} Direction;

typedef struct {
	float x, y;
} coord;

typedef struct {
  coord position;
  int vie;
  int roundsGagnes;
  int action;
  bool sauter;
  Direction direction;
	Personnage perso;
	SDL_Rect hitbox; //Hitbox pour recevoir des degats et le reste
	SDL_Rect hitbox_coup; //Hitbox pour la portée des coups de poing
  SDL_Rect hitbox_pied; //Hitbox pour la portée des coups de pieds
	SDL_Texture * texture;
} Joueur;

/**
 * @brief Fonction pour savoir si le joueur dépasse la hauteur maximale
 * 
 * @param joueur Structure joueur du joueur à tester
 * @return true return vrai si est trop haut
 * @return false return faux si n'est pastrop haut
 */
bool estTropHaut(Joueur * joueur);

/**
 * @brief Fonction pour savoir si le joueur est au sol
 * 
 * @param joueur Structure joueur du joueur à tester
 * @return true return vrai si le joueur est au sol
 * @return false return faux si le joueur est en l'air
 */
bool estAuSol(Joueur * joueur);

/**
 * @brief Fonction qui retourne les joueurs en fonction de leur position respectives
 * 
 * @param j1 Structure joueur du joueur 1
 * @param j2 Structure joueur du joueur 2
 */
void direction(Joueur * j1, Joueur * j2);

/**
 * @brief Fonction de création des hitbox du coup de pied ou poing et les affiche si extern debug = vrai
 * 
 * @param joueur hitbox du joueur à créer
 * @param texture texture de la hitbox à afficher
 * @param coup vaut 1 si coup de poing sinon 2 pour coup de pied
 */
void hitbox(Joueur * joueur, SDL_Texture * texture,int coup);

/**
 * @brief Fonction qui teste si l'un des deux joueurs à perdu
 * 
 * @param j1 Structure joueur du joueur 1
 * @param j2 Structure joueur du joueur 2
 * @return int \li vaut 0 si personne à perdu \li vaut 1 si J1 à perdu \li vaut 2 si J2 à perdu
 */
int checkPerdu(Joueur * j1, Joueur * j2);

/**
 * @brief Fonction qui teste la collision de la hitbox de coup ( pied ou poing en fonction de l'action ) de hitbox du J2
 * 
 * @param j1 Structure joueur du joueur attaquant
 * @param j2 Structure joueur du joueur qui se prend le coup
 * @return true return vrai si collision
 * @return false return vrai si pas de collision
 */
bool checkCollisions(Joueur * j1, Joueur * j2);

/**
 * @brief Fonction qui initialise les valeurs d'un joueur ( vie / position / direction / texture)
 * 
 * @param joueur Joueur à initialiser
 * @param posX position du joueur que l'on veut lui affecter
 * @param texture texture du joueur à affecter
 * @param direction direction que l'on va lui affecter
 */
void initJoueur(Joueur * joueur, float posX, SDL_Texture * texture, Direction direction);

/**
 * @brief Fonction affectant un personnage à un joueur
 * 
 * @param j Structure du joueur à laquelle on affecte le perso
 * @param i numero du perso à affecter
 */
void initPerso(Joueur * j, int i);
#endif
