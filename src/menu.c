/**
 * @file menu.c
 * @author Notelet Léo, Pecquery Charly, Guimbert Alexis
 * @brief fichier qui gère le lancement des différents menus
 * @version 0.1
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
 * @brief fonction qui redirige vers un des menus
 * 
 * @param menu numéro du menu
 * @param drip option d'affichage
 * @param ia variable qui vérifie si l'on est en joueur contre joueur ou joueur contre IA
 */
void lancerMenu(int menu, int drip, int ia){
  switch (menu) {
    case MENU_PRINCIPAL: menu_principal(drip); break;
    case MENU_SELECTION: menu_selection(drip,ia); break;
    case MENU_OPTIONS: menu_option(drip); break;
  }
}

/**
 * @brief 
 * 
 * @param font police d'écriture
 * @param texte texte à afficher
 * @param couleur couleur du texte
 * @param rect rectangle dans laquelle est affiché le texte
 * @param texture stocke les textures
 * @param x coordoné x du rectangle
 * @param y coordoné y du rectangle
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
 * @brief fonctions qui affiche des flammes
 * 
 * @param rect rectangle où sera affiché les flammes 
 * @param texture tableau de pointeurs des textures des flammes
 * @param x emplacement x des flammes
 * @param y emplacement y des flammes
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