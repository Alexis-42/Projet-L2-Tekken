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
#include "../include/gui.h"

#define MODE BORDERLESS
int sec_deb_combat,ancien_temps=-1;
bool quit;
SDL_DisplayMode ecran;

void initSdl(Joueur * j1, Joueur * j2, int num_map) { //Créer la fenêtre et l'environnement (pour l'instant)
  quit = false;
  SDL_Texture * tex_menu_Principal = NULL;
  SDL_Texture * texture_carre_jaune = NULL;
  SDL_Texture * texture_carre_rouge = NULL;
  SDL_Texture * texture_barre_de_vie = NULL;
  SDL_Texture * texture_nomj1 = NULL;
  SDL_Texture * texture_nomj2 = NULL;
  SDL_Texture * texture_temps = NULL;
  SDL_Rect srcBg, dstBg, rect_sprite_pv_j1, rect_sprite_pv_j2,rect_nom_j1, rect_nom_j2,rect_temps;

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

  char j1sprite[50], j2sprite[50];
  snprintf(j1sprite, sizeof(j1sprite), "res/sprites/%s.png", j1->perso.nom);
  snprintf(j2sprite, sizeof(j2sprite), "res/sprites/%s.png", j2->perso.nom);

  SDL_Surface * perso1 = IMG_Load(j1sprite);
  SDL_Surface * perso2 = IMG_Load(j2sprite);

  chargerMap(num_map, renderer,1);

  SDL_Texture * texture_joueur1 = SDL_CreateTextureFromSurface(renderer, perso1);
  SDL_Texture * texture_joueur2 = SDL_CreateTextureFromSurface(renderer, perso2);
  SDL_FreeSurface(perso1);
  SDL_FreeSurface(perso2);

  TTF_Init();

  initJoueur(j1, 300.0, "Shrekleouinouin", texture_joueur1, gauche);
  initJoueur(j2, 600.0, "PINGU", texture_joueur2, droite);
  resetAnimation(j1); //Spawn du joueur
  resetAnimation(j2);

  init_sprite_pv(&rect_sprite_pv_j1, 1);
  init_sprite_pv(&rect_sprite_pv_j2, 2);

  SDL_Surface * sprite_barre_de_vie = IMG_Load("res/barre_de_vie.png");
  init_gui(&texture_carre_jaune, &texture_carre_rouge, sprite_barre_de_vie, &texture_barre_de_vie);

  TTF_Font * font = NULL;
  font = TTF_OpenFont("res/fonts/Sans.ttf", 50);

  init_afficher_nom_joueur(j1, font, &rect_sprite_pv_j1, &rect_nom_j1, &texture_nomj1,1);
  init_afficher_nom_joueur(j2, font, &rect_sprite_pv_j2, &rect_nom_j2, &texture_nomj2,2);

  while (!quit ) {
    Uint8 *state = SDL_GetKeyboardState(NULL);
    sec_deb_combat = SDL_GetTicks()/1000;
    jouerAnimationBackground(&srcBg, &dstBg,1);

    checkPerdu(j1, j2);
    jouerAnimation(j1);
    jouerAnimation(j2);
    deplacements(j1, j2);
    SDL_RenderClear(renderer);
    renderMap(&srcBg, &dstBg, renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); //Couleur des hitboxes
    SDL_RenderFillRect(renderer, &(j1->hitbox));
    SDL_RenderFillRect(renderer, &(j2->hitbox));
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0); //Couleur des hitboxes
    SDL_RenderFillRect(renderer, &(j1->hitbox_coup));
    SDL_RenderFillRect(renderer, &(j2->hitbox_coup));
    
    renderAnimation(j1);
    renderAnimation(j2);
   
   
    barre_de_vie(j1, &rect_sprite_pv_j1, texture_barre_de_vie, texture_carre_rouge, texture_carre_jaune, 1, font);
    barre_de_vie(j2, &rect_sprite_pv_j2, texture_barre_de_vie, texture_carre_rouge, texture_carre_jaune, 2, font);
    init_affichage_temps(sec_deb_combat, font, &rect_sprite_pv_j1, &texture_temps, &rect_temps);
    SDL_RenderCopy(renderer, texture_temps, NULL ,&rect_temps);
    SDL_DestroyTexture(texture_temps);

    SDL_RenderCopy(renderer, texture_nomj1, NULL ,&rect_nom_j1);
    SDL_RenderCopy(renderer, texture_nomj2, NULL ,&rect_nom_j2);
    SDL_RenderPresent(renderer);
    quit = sec_deb_combat >59 || state[SDL_SCANCODE_ESCAPE];
  }


  SDL_RenderClear(renderer);
  SDL_DestroyTexture(texture_nomj1);
  SDL_DestroyTexture(texture_nomj2);
  SDL_DestroyTexture(texture_carre_rouge);
  SDL_DestroyTexture(texture_carre_jaune);
  SDL_DestroyTexture(texture_barre_de_vie);
  SDL_DestroyTexture(tex_menu_Principal);
  SDL_DestroyTexture(texture_joueur1);
  SDL_DestroyTexture(texture_joueur2);
  SDL_FreeSurface(sprite_barre_de_vie);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
