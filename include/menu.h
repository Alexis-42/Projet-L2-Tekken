/**
 * @file menu.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header contenant les fonctions qui permettent de faire l'affichage des menus
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define MENU_PRINCIPAL 0
#define MENU_SELECTION 1
#define MENU_PAUSE 2
#define MENU_OPTIONS 3


/**
 * @brief Lance un des trois menus du jeu
 * 
 * @param menu Numero du menu à lancer \li 1 = menu principal \li 2 = menu selection \li 3 = menu option
 * @param drip Valeur qui sert de flag pour le secret du jeu
 * @param ia Valeur qui sert de flag pour le mode vs ia
 */
void lancerMenu(int menu, int drip, int ia);

/**
 * @brief Fonction qui permet d'initialiser les valeurs de la texture et rectangle d'un bouton
 * 
 * @param font Font à utiliser
 * @param texte Texte à écrire sur le bouton
 * @param couleur Couleur à utiliser pour l'écriture
 * @param rect Rectangle à remplir
 * @param texture Texture à remplir
 * @param x position x du bouton
 * @param y position y du bouton
 */
void creerBouton(TTF_Font * font, char * texte, SDL_Color couleur, SDL_Rect * rect, SDL_Texture ** texture, float x, float y);

/**
 * @brief Fonction qui permet d'initialiser les valeurs de la texture et rectangle des flammes à mettre derrière un bouton
 * 
 * @param rect Rectangle à remplir
 * @param texture Texture à remplir
 * @param x position x des flammes
 * @param y position y des flammes
 */
void initFlammes(SDL_Rect * rect, SDL_Texture ** texture, float x, float y);