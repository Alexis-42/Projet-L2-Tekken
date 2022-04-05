/**
 * @file menu.c
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonctions qui permettent de faire l'affichage des menus
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/jeu.h"
#include "../include/menu.h"
#include "../include/menu_principal.h"
#include "../include/menu_selection.h"
#include "../include/options.h"

/**
 * @brief Lance un des trois menus du jeu
 * 
 * @param menu Numero du menu à lancer \li 1 = menu principal \li 2 = menu selection \li 3 = menu option
 * @param drip Valeur qui sert de flag pour le secret du jeu
 * @param ia Valeur qui sert de flag pour le mode vs ia
 */
void lancerMenu(int menu, int drip, int ia){
  switch (menu) {
    case MENU_PRINCIPAL: menu_principal(drip); break;
    case MENU_SELECTION: menu_selection(drip,ia); break;
    case MENU_OPTIONS: menu_option(drip); break;
  }
}

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
void creerBouton(TTF_Font * font, char * texte, SDL_Color couleur, SDL_Rect * rect, SDL_Texture ** texture, float x, float y){
  SDL_Surface * surface_jouer_multi = TTF_RenderText_Solid(font, texte, couleur);
  *texture = SDL_CreateTextureFromSurface(renderer, surface_jouer_multi);
  int text_width_jouer_multi = surface_jouer_multi->w;
  int text_height_jouer_multi = surface_jouer_multi->h;
  SDL_FreeSurface(surface_jouer_multi);

  SDL_Rect rect_jouer_multi;

  rect_jouer_multi.x = x/1920.0*ecran.w;
  rect_jouer_multi.y = y/1080.0*ecran.h;
  rect_jouer_multi.w = text_width_jouer_multi;
  rect_jouer_multi.h = text_height_jouer_multi;

  *rect=rect_jouer_multi;
}


/**
 * @brief Fonction qui permet d'initialiser les valeurs de la texture et rectangle des flammes à mettre derrière un bouton
 * 
 * @param rect Rectangle à remplir
 * @param texture Texture à remplir
 * @param x position x des flammes
 * @param y position y des flammes
 */
void initFlammes(SDL_Rect * rect, SDL_Texture ** texture, float x, float y){
  SDL_Surface * image_flamme_multi = IMG_Load("res/selection/flamme.png");
  *texture = SDL_CreateTextureFromSurface(renderer, image_flamme_multi);
  int text_width_flamme_multi = image_flamme_multi->w;
  int text_height_flamme_multi = image_flamme_multi->h;

  SDL_FreeSurface(image_flamme_multi);
  SDL_Rect rect_flamme_multi;
  rect_flamme_multi.x = x/1920.0*ecran.w;
  rect_flamme_multi.y = y/1080.0*ecran.h;
  rect_flamme_multi.w = text_width_flamme_multi+600.0;
  rect_flamme_multi.h = text_height_flamme_multi+50.0;
  *rect=rect_flamme_multi;
}
