/**
 * @file map.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header des fonctions qui chargent les map et render
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

extern float spawnY;
extern int nbFramesMap;
extern int pas;
extern int h_map;
extern int h_map2;
extern int pas2;

#define stage1 0
#define stage2 1
#define stage3 3

/**
 * @brief Affiche une carte à l'écran ( sur le renderer )
 * 
 * @param src rectangle source de la texture à selectionner
 * @param dst rectangle de desination du renderer à afficher
 * @param renderer renderer sur lequel appliquer l'affichage de la carte
 */
void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer);

/**
 * @brief Fonction de chargement des valeurs extern et de la texure en fonction du numéro de map séléctionné
 * 
 * @param map numéro de la carte à charger
 * @param renderer renderer sur lequel afficher la carte
 * @param flag_bg flag indiquant si il s'agit de la carte du menu selection ( = carte en plut petit ) ou pas \li vaut 1 si carte \li vaut 2 si minicarte du menu selection
 * @param drip flag secret qui sert à charger la map secrète
 */
void chargerMap(int map, SDL_Renderer * renderer, int flag_bg, int drip);
