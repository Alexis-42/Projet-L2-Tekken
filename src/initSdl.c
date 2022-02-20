#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/deplacements.h"
#include "../include/main.h"
#include "../include/menu_principal.h"
#include "../include/joueur.h"
#include "../include/animations.h"

#define MODE BORDERLESS

bool quit;
int x_destrec, y_destrec;

void initSdl() { //Créer la fenêtre et l'environnement (pour l'instant)
  quit = false;
  SDL_Window * window;
  SDL_DisplayMode ecran;
  SDL_Texture * tex_menu_Principal = NULL;
  SDL_Rect rect1;
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  SDL_GetDesktopDisplayMode(0, &ecran);

  switch(MODE){
    case FULLSCREEN: window = SDL_CreateWindow("SDL2 Tekken",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_FULLSCREEN);
    break;
    case BORDERLESS: window = SDL_CreateWindow("SDL2 Tekken",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_BORDERLESS);
    break;
    default: window = SDL_CreateWindow("SDL2 Tekken",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w / 2, ecran.h / 2, 0);
  }

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Surface * image_perso = IMG_Load("res/sprites/Pingu.png");
  SDL_Surface * image_stage = IMG_Load("res/backgrounds/stage2.png");
  SDL_Texture * texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image_perso);

  // SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
  // SDL_RenderClear(renderer);
  x_destrec = 128;
  y_destrec = 680;

  TTF_Init();
  menu_principal(renderer, &ecran, &tex_menu_Principal, &rect1);
  Joueur j;
  initJoueur(&j);

  while (!quit) {
    actions(); //Appelle la fonction dans le main pour que les actions s'actualisent
    jouerAnimation(COURIR, &j);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_stage, NULL, NULL);
    SDL_RenderCopy(renderer, tex_menu_Principal, NULL, &rect1);
    SDL_RenderCopy(renderer, texture, j.srcrect, j.dstrect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture_stage);
  SDL_DestroyTexture(tex_menu_Principal);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image_perso);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
