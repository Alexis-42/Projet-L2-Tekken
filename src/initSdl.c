#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/deplacements.h"
#include "../include/menu_principal.h"
#include "../include/joueur.h"
#include "../include/animations.h"
#include "../include/jeu.h"
#include "../include/personnages.h"

#define MODE FULLSCREEN

bool quit;
SDL_DisplayMode ecran;

void initSdl() { //Créer la fenêtre et l'environnement (pour l'instant)
  quit = false;
  SDL_Texture * tex_menu_Principal = NULL;
  SDL_Rect rect1, srcBg, dstBg;

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
  renderer = SDL_CreateRenderer(window, -1, 0);
  Joueur j1, j2;
  initPerso(&j1, 0); //Pingu
  initPerso(&j2, 1); //Shrek

  char j1sprite[50], j2sprite[50];
  snprintf(j1sprite, sizeof(j1sprite), "res/sprites/%s.png", j1.perso.nom);
  snprintf(j2sprite, sizeof(j2sprite), "res/sprites/%s.png", j2.perso.nom);

  SDL_Surface * perso1 = IMG_Load(j1sprite);
  SDL_Surface * perso2 = IMG_Load(j2sprite);

  SDL_Surface * image_stage = IMG_Load("res/backgrounds/stage.png");
  SDL_Texture * texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);

  SDL_Texture * texture_joueur1 = SDL_CreateTextureFromSurface(renderer, perso1);
  SDL_Texture * texture_joueur2 = SDL_CreateTextureFromSurface(renderer, perso2);

  TTF_Init();

  initJoueur(&j1, 300.0, "PINGUU", texture_joueur1, gauche);
  initJoueur(&j2, 600.0, "Shrekleouinouin", texture_joueur2, droite);
  resetAnimation(&j1); //Spawn du joueur
  resetAnimation(&j2);
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); //Couleur des hitboxes

  while (!quit) {
    jouerAnimationBackground(&srcBg, &dstBg);
    jouerAnimation(&j1);
    deplacements(&j1, &j2);
    checkPerdu(&j1, &j2);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_stage, &srcBg, &dstBg);
    renderAnimation(&j1);
    renderAnimation(&j2);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture_stage);
  SDL_DestroyTexture(tex_menu_Principal);
  SDL_DestroyTexture(texture_joueur1);
  SDL_DestroyTexture(texture_joueur2);
  SDL_FreeSurface(perso1);
  SDL_FreeSurface(perso2);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
