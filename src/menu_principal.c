#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/initSdl.h"
#include "../include/deplacements.h"

void ajouterTexte(SDL_Renderer *renderer, int x, int y, char *text, char * cheminPolice, int taille, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    TTF_Font *font = TTF_OpenFont(cheminPolice, taille);
    if (font == NULL) {
          fprintf(stderr, "error: font not found\n");
          exit(EXIT_FAILURE);
    }

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

void menu_principal(SDL_Renderer * renderer, SDL_DisplayMode * ecran, SDL_Texture ** texture, SDL_Rect * rect){
  ajouterTexte(renderer, ecran->w/2, ecran->h/2, "Jouer", "res/fonts/WRESTLEMANIA.ttf", 24, texture, rect);
}
