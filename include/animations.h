/**
 * @file animations.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonctions en relation avec les variables d'animations
 * @version 1.0
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../include/joueur.h"
#ifndef ANIM_H_INCLUDED__
#define ANIM_H_INCLUDED__
#define DANSE 0
#define DEGAT 1
#define IDLE 2
#define MORT 3
#define PIED 4
#define POING 5
#define COURIR 6
#define SAUTER 7
#define PARER 8
/**
 * @brief passe l'animation d'un joueur au renderer à l'aide du paramètre joueur
 * 
 * @param joueur structure joueur
 */
void renderAnimation(Joueur * joueur);

/**
 * @brief permet de mettre les valeurs [srect, destrect et action] de la structure joueur à des valeurs par default
 * 
 * @param joueur structure joueur
 */
void resetAnimation(Joueur * joueur);

/**
 * @brief décalle le sprite en fonction de l'action pour l'animer
 * 
 * @param joueur structure joueur
 */
void jouerAnimation(Joueur * joueur);

/**
 * @brief Change les deux rectangles du rendercopy pour animer le background met aussi à jour les variables globales \p h_map & \p pas si \p flag_bg = 1 sinon met à jour \p h_map2 & \p pas2
 * @param srcBg rectangle dans le fichier source à décaller pour animer le background
 * @param dstBg rectangle d'affichage sur l'ecran en fonction de la taille de l'écran \n -optionnel si jamais flag_bg = 0
 * @param flag_bg prend les valeurs \n 1 = background, 0 = preview \n si jamais on veut l'afficher sur tout l'ecran on met 1 sinon 0 qui est utilisé dans le menu selection de la carte
 */
void jouerAnimationBackground(SDL_Rect * srcBg, SDL_Rect * dstBg,int flag_bg);

/**
 * @brief structure représentant les informations qui permettent de générer une map & connaitre la position de départ des joueurs
 * @param posY position de départ des joueurs en Y
 * @param nb_frames nombres de frame de l'animation pour un background en particulier
 * @param chemin_sprite Chaine de caractère représentant le chemin du sprite
 */
typedef struct {
  int posY; 
  int nb_frames;
  char * chemin_sprite; 
} Background;

#endif
