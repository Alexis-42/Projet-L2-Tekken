/**
 * @file gui.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonction d'affichage de l'interface utilisateur et l'initialisation des valeurs importantes à cet affichage
 * @version 1.2
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../include/joueur.h"
#ifndef GUI_H_INCLUDED__
#define GUI_H_INCLUDED__

/**
 * @brief Fonction qui initialise les textures qui sont en relation avec le temps
 * 
 * @param temps_combat Le temps actuel du combat
 * @param font La font que l'on veut
 * @param rect_sprite_pvj1 Rectangle qui sera utilisé pour afficher la vie du joueur
 * @param texture texture à entrer afin de la créer
 * @param rect_temps Rectangle qui sera utilisé pour afficher le temps
 */
void init_affichage_temps(int temps_combat, TTF_Font* font, SDL_Rect * rect_sprite_pvj1, SDL_Texture **texture,SDL_Rect * rect_temps);

/**
 * @brief fonction qui permet d'initialiser les valeurs du réctangle d'un sprite barre de vie en fonction du joueur
 * 
 * @param rect_sprite_pv Rectangle à initisialiser
 * @param num_joueur Numero du joueur : @li 1 pour j1 @li 2 pour j2
 */
void init_sprite_pv(SDL_Rect * rect_sprite_pv,int num_joueur);

/**
 * @brief Initialise les textures et rectangles qui sont en relation avec l'affichage du nom des joueurs
 * 
 * @param joueur Joueur auquel on va afficher le nom
 * @param font Font à utiliser
 * @param rect_sprite_pv Rectangle de la barre de vie afin d'avoir sa position
 * @param rect_nom_joueur Rectangle dans lequel on va ecrire le nom du joueur ( en dessous de sa barre de vie )
 * @param texture Texture à initialiser
 * @param num_joueur Numero du joueur : @li 1 pour j1 @li 2 pour j2
 */
void init_afficher_nom_joueur(Joueur * joueur, TTF_Font* font, SDL_Rect * rect_sprite_pv, SDL_Rect * rect_nom_joueur, SDL_Texture ** texture, int num_joueur);

/**
 * @brief Fonction à appeler pour afficher les barres de vies apres l'init ( à utiliser pour redessiner la barre à chaque appel )
 * 
 * @param joueur Joueur auquel on va afficher le nom
 * @param rect_sprite_pv Rectangle de la partie grise de la barre de vie
 * @param texture_barre_de_vie Texture de la partie grise de la barre de vie
 * @param texture_carre_rouge Texture du carré rouge
 * @param texture_carre_jaune Texture du carré jaune
 * @param font Font à utiliser
 */
void barre_de_vie(Joueur * joueur, SDL_Rect * rect_sprite_pv, SDL_Texture * texture_barre_de_vie, SDL_Texture * texture_carre_rouge, SDL_Texture * texture_carre_jaune, TTF_Font* font);

/**
 * @brief Fonction qui va initialiser les textures d'une barre de vie
 * 
 * @param texture_carre_jaune texture du carée jaune à initialiser
 * @param texture_carre_rouge texture du carée rouge à initialiser
 * @param sprite_barre_de_vie surface entrée en paramètre du contour gris
 * @param texture_barre_de_vie texture du contour gris à initialiser
 */
void init_gui(SDL_Texture ** texture_carre_jaune, SDL_Texture ** texture_carre_rouge, SDL_Surface * sprite_barre_de_vie, SDL_Texture ** texture_barre_de_vie);

#endif
