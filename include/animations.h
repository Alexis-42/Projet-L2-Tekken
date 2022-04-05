/**
 * @file animations.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonction header d'affichage du jeu \li Jouer animation perso \li Attaquer un joueur \li Jouer animation background
 * \n ainsi que la structure background
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
 * @brief Anime un joueur grâce à ses données dans la structure qui lui correspond
 * 
 * @param joueur Joueur qui va etre animé dans cette frame
 */
void renderAnimation(Joueur * joueur);
/**
 * @brief 
 * 
 * @param joueur 
 * @param seconds 
 * @param j2 
 */
void jouerAnimation(Joueur * joueur,int seconds,Joueur * j2);

/**
 * @brief 
 * 
 * @param joueur 
 * @param seconds 
 */
void jouerAnimationContinu(Joueur * joueur,int seconds);

/**
 * @brief Initialise les valeurs des rectangles afin d'animer un fond ( en mode preview ou en background )
 * 
 * @param srcBg Rectangle qui va être utilisé pour lire une partie de sprite ( chargée dans une texture )
 * @param dstBg Rectangle d'affichage sur l'écran
 * @param flag_bg @li = 1 si on veut animer un background @li = 2 si on veut animer une preview ( menu selection )
 */
void jouerAnimationBackground(SDL_Rect * srcBg, SDL_Rect * dstBg,int flag_bg);

/**
 * @struct Background
 * @param posY position en Y du spawn des joueurs
 * @param nb_frames nombre d'image du sprite de ce background
 * @param chemin_sprite Chemin du sprite à utiliser pour un background
 */
typedef struct {
  int posY;
  int nb_frames;
  char * chemin_sprite;
} Background;

#endif
