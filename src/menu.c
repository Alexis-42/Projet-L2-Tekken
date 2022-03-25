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

void lancerMenu(int menu){
  switch (menu) {
    case MENU_PRINCIPAL: menu_principal(); break;
    case MENU_SELECTION: menu_selection(); break;
  }
}

void creerBouton(SDL_Renderer * renderer, TTF_Font * font, char * texte, SDL_Color couleur, SDL_Rect * rect, SDL_Texture ** texture, float x, float y){
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