/**
 * @file joueur.c
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonctions à propos des joueurs ( test / initialisation / affichage hitbox)
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"
#include "../include/personnages.h"
#include "../include/map.h"
#include "../include/options.h"

/**
 * @brief Fonction pour savoir si le joueur dépasse la hauteur maximale
 * 
 * @param joueur Structure joueur du joueur à tester
 * @return true return vrai si est trop haut
 * @return false return faux si n'est pastrop haut
 */
bool estTropHaut(Joueur * joueur){
  return joueur->position.y<=0;
}

/**
 * @brief Fonction pour savoir si le joueur est au sol
 * 
 * @param joueur Structure joueur du joueur à tester
 * @return true return vrai si le joueur est au sol
 * @return false return faux si le joueur est en l'air
 */
bool estAuSol(Joueur * joueur){
  if(strcmp(joueur->perso.nom,"Mickey")==0)
    return joueur->position.y>=(((spawnY-2) - (joueur->perso.taille_perso.h-85* joueur->perso.taille_perso.mult) )/1080.0)*ecran.h;
  return joueur->position.y>=(((spawnY-2) - (joueur->perso.taille_perso.h) )/1080.0)*ecran.h;
}


/**
 * @brief Fonction qui retourne les joueurs en fonction de leur position respectives
 * 
 * @param j1 Structure joueur du joueur 1
 * @param j2 Structure joueur du joueur 2
 */
void direction(Joueur * j1, Joueur * j2){
    j1->direction=j1->position.x<j2->position.x; //Direction
    j2->direction=j1->position.x>j2->position.x;
}

/**
 * @brief Fonction de création des hitbox du coup de pied ou poing et les affiche si extern debug = vrai
 * 
 * @param joueur hitbox du joueur à créer
 * @param texture texture de la hitbox à afficher
 * @param coup vaut 1 si coup de poing sinon 2 pour coup de pied
 */
void hitbox(Joueur * joueur, SDL_Texture * texture,int coup){
  SDL_Rect hitbox = {
    joueur->position.x+joueur->perso.hitbox_offsetX/joueur->perso.taille_perso.mult,
    joueur->position.y+joueur->perso.hitbox_offsetY/joueur->perso.taille_perso.mult,
    joueur->perso.taille_hitbox.w,
    joueur->perso.taille_hitbox.h
  };
  SDL_Rect hitbox2;

  if(coup){
      if(joueur->direction == droite){
        hitbox2.x = hitbox.x;
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_coup.w;
        hitbox2.h = joueur->hitbox_coup.h; 
      }if(joueur->direction == gauche){
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_coup.w;
        hitbox2.x = (hitbox.x+hitbox.w)-hitbox2.w;
        hitbox2.h = joueur->hitbox_coup.h;   
      }
     joueur->hitbox_coup=hitbox2;
    }else{
      // si le joueur est tourné à droite
      if(joueur->direction == droite){
        hitbox2.x = hitbox.x;
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_pied.w;
        hitbox2.h = joueur->hitbox_pied.h;  
      }if(joueur->direction == gauche){
        hitbox2.y = hitbox.y;
        hitbox2.w = joueur->hitbox_pied.w;
        hitbox2.x = (hitbox.x+hitbox.w)-hitbox2.w;
        hitbox2.h = joueur->hitbox_pied.h;  
      }
      joueur->hitbox_pied=hitbox2;
    }
  joueur->hitbox=hitbox;

  if(debug)
    SDL_RenderCopy(renderer, texture ,NULL , &hitbox2);
}

/**
 * @brief Fonction qui teste si l'un des deux joueurs à perdu
 * 
 * @param j1 Structure joueur du joueur 1
 * @param j2 Structure joueur du joueur 2
 * @return int \li vaut 0 si personne à perdu \li vaut 1 si J1 à perdu \li vaut 2 si J2 à perdu
 */
int checkPerdu(Joueur * j1, Joueur * j2){
	if(j1->vie<=0)
		return 1;
	else if(j2->vie<=0)
		return 2;
  return 0;
}

/**
 * @brief Fonction qui teste la collision de la hitbox de coup ( pied ou poing en fonction de l'action ) de hitbox du J2
 * 
 * @param j1 Structure joueur du joueur attaquant
 * @param j2 Structure joueur du joueur qui se prend le coup
 * @return true return vrai si collision
 * @return false return vrai si pas de collision
 */
bool checkCollisions(Joueur * j1, Joueur * j2){
	SDL_bool collision = SDL_FALSE;
  //if(j1->action == POING)
  if(j1->action == PIED)
	  collision = SDL_HasIntersection(&(j1->hitbox_pied), &(j2->hitbox));
  else
    collision = SDL_HasIntersection(&(j1->hitbox_coup), &(j2->hitbox));

	return collision==SDL_TRUE;
}

/**
 * @brief Fonction qui initialise les valeurs d'un joueur ( vie / position / direction / texture)
 * 
 * @param joueur Joueur à initialiser
 * @param posX position du joueur que l'on veut lui affecter
 * @param texture texture du joueur à affecter
 * @param direction direction que l'on va lui affecter
 */
void initJoueur(Joueur * joueur, float posX, SDL_Texture * texture, Direction direction){
  joueur->vie=100;
  joueur->action=IDLE;
  joueur->sauter=false;
  joueur->texture=texture;
  joueur->direction=direction;
  joueur->position.x=(posX/1280.0)*ecran.w;
  if(strcmp(joueur->perso.nom,"Mickey")==0)
    joueur->position.y= ( (spawnY - (joueur->perso.taille_perso.h-(85* joueur->perso.taille_perso.mult)) )/1080.0)*ecran.h;
  else
    joueur->position.y= ( (spawnY - joueur->perso.taille_perso.h )/1080.0)*ecran.h;
  joueur->perso.frame=0;
}
