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
#include "../include/map.h"

#define MODE FULLSCREEN

bool quit;
SDL_DisplayMode ecran;
SDL_Texture * text_viej1 = NULL;
SDL_Texture * text_viej2 = NULL;

void initSdl() { //Créer la fenêtre et l'environnement (pour l'instant)
  quit = false;
  SDL_Texture * tex_menu_Principal = NULL;
  SDL_Rect srcBg, dstBg, rect_sprite_pv_j1, rect_sprite_pv_j2;

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
  initPerso(&j1, PINGU);
  initPerso(&j2, PINGU);

  char j1sprite[50], j2sprite[50];
  snprintf(j1sprite, sizeof(j1sprite), "res/sprites/%s.png", j1.perso.nom);
  snprintf(j2sprite, sizeof(j2sprite), "res/sprites/%s.png", j2.perso.nom);

  SDL_Surface * perso1 = IMG_Load(j1sprite);
  SDL_Surface * perso2 = IMG_Load(j2sprite);

  chargerMap(2, renderer);

  SDL_Texture * texture_joueur1 = SDL_CreateTextureFromSurface(renderer, perso1);
  SDL_Texture * texture_joueur2 = SDL_CreateTextureFromSurface(renderer, perso2);

  TTF_Init();

  initJoueur(&j1, 300.0, "Shrekleouinouin", texture_joueur1, gauche);
  initJoueur(&j2, 600.0, "PINGU", texture_joueur2, droite);
  resetAnimation(&j1); //Spawn du joueur
  resetAnimation(&j2);
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0); //Couleur des hitboxes

  init_sprite_pv(&rect_sprite_pv_j1, 1);
  init_sprite_pv(&rect_sprite_pv_j2, 2);

  SDL_Surface * sprite_barre_de_vie = IMG_Load("res/barre_de_vie.png");

  while (!quit) {
    jouerAnimationBackground(&srcBg, &dstBg);
    jouerAnimation(&j1);
    deplacements(&j1, &j2);
    checkPerdu(&j1, &j2);
    SDL_RenderClear(renderer);
    renderMap(&srcBg, &dstBg, renderer);
    renderAnimation(&j1);
    renderAnimation(&j2);
    text_viej1 = barre_de_vie(&j1, &rect_sprite_pv_j1, sprite_barre_de_vie, renderer,1); 
    text_viej2 = barre_de_vie(&j2, &rect_sprite_pv_j2, sprite_barre_de_vie, renderer, 2);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(text_viej1);
    SDL_DestroyTexture(text_viej2);
  }


  //SDL_DestroyTexture(texture_stage);
  SDL_DestroyTexture(tex_menu_Principal);
  SDL_DestroyTexture(texture_joueur1);
  SDL_DestroyTexture(texture_joueur2);
  SDL_FreeSurface(sprite_barre_de_vie);
  SDL_FreeSurface(perso1);
  SDL_FreeSurface(perso2);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
