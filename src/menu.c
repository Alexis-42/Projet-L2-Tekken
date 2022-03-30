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

void lancerMenu(int menu, int drip, int ia){
  switch (menu) {
    case MENU_PRINCIPAL: menu_principal(drip); break;
    case MENU_SELECTION: menu_selection(drip,ia); break;
    case MENU_OPTIONS: menu_option(drip); break;
  }
}

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

  void initFlammes(SDL_Rect * rect, SDL_Texture ** texture, float x, float y){
    SDL_Surface * image_flamme_multi = IMG_Load("res/flamme.png");
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