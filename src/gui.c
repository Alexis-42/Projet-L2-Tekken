/**
 * @file gui.c
 * @brief Fonctions relatives au gui ( Graphical User Interface )
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/gui.h"

#define OFFSET 26

void init_gui(SDL_Texture ** texture_carre_jaune, SDL_Texture ** texture_carre_rouge, SDL_Surface * sprite_barre_de_vie, SDL_Texture ** texture_barre_de_vie){
  SDL_Surface * image_carre_jaune = IMG_Load("res/barre_jaune.png");
  *texture_carre_jaune = SDL_CreateTextureFromSurface(renderer, image_carre_jaune);
  SDL_FreeSurface(image_carre_jaune);

  SDL_Surface * image_carre_rouge = IMG_Load("res/barre_rouge.png");
  *texture_carre_rouge = SDL_CreateTextureFromSurface(renderer, image_carre_rouge);
  SDL_FreeSurface(image_carre_rouge);

  *texture_barre_de_vie = SDL_CreateTextureFromSurface(renderer, sprite_barre_de_vie);
}

/**
 * @brief Fonction qui initialise les textures qui sont en relation avec le temps
 * 
 * @param sec_deb_combat Le temps actuel du combat
 * @param font La font que l'on veut
 * @param rect_sprite_pvj1 Rectangle qui sera utilisé pour afficher la vie du joueur
 * @param texture texture à entrer afin de la créer
 * @param rect_temps Rectangle qui sera utilisé pour afficher le temps
 */
void init_affichage_temps(int sec_deb_combat,TTF_Font* font, SDL_Rect * rect_sprite_pvj1, SDL_Texture **texture,SDL_Rect * rect_temps){
 // sachant que ces deux temps sont en secondes on regenere les textures que si la seconde est differente
  char str_temps[3];
  SDL_Color textColor = {255, 255, 255, 0};
  rect_temps->x = rect_sprite_pvj1->x+rect_sprite_pvj1->w;
  rect_temps->y = rect_sprite_pvj1->y;
  rect_temps->w = ecran.w-(2*rect_sprite_pvj1->w);
  rect_temps->h = rect_sprite_pvj1->h;
  snprintf(str_temps, sizeof(str_temps), "%i", 60-sec_deb_combat);

  SDL_Surface * surface = TTF_RenderText_Solid(font, str_temps, textColor);
  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

/**
 * @brief fonction qui permet l'init d'un sprite barre de vie en fonction du joueur
 * 
 * @param rect_sprite_pv Rectangle à initisialiser
 * @param num_joueur Numero du joueur : @li 1 pour j1 @li 2 pour j2
 */
void init_sprite_pv(SDL_Rect * rect_sprite_pv, int num_joueur){
  rect_sprite_pv->y = 0;
  rect_sprite_pv->w = (int)(0.44*ecran.w);
  rect_sprite_pv->h = (int)(0.13*ecran.h);
  if(num_joueur==1){
    rect_sprite_pv->x = 0;
  }else{
    rect_sprite_pv->x = ecran.w-rect_sprite_pv->w;
  }
}

/**
 * @brief Initialise les textures et rectangle qui sont en relation avec l'affichage du nom des joueurs
 * 
 * @param joueur Joueur auquel on va afficher le nom
 * @param font Font à utiliser
 * @param rect_sprite_pv Rectangle de la barre de vie afin d'avoir sa position
 * @param rect_nom_joueur Rectangle dans lequel on va ecrire le nom du joueur ( en dessous de sa barre de vie )
 * @param texture Texture à initialiser
 * @param num_joueur Numero du joueur : @li 1 pour j1 @li 2 pour j2
 */
void init_afficher_nom_joueur(Joueur * joueur, TTF_Font* font, SDL_Rect * rect_sprite_pv, SDL_Rect * rect_nom_joueur, SDL_Texture ** texture, int num_joueur){
  int len_nom = strlen(joueur->perso.nom);
  SDL_Color textColor = {255, 255, 255, 0};
  rect_nom_joueur->y = rect_sprite_pv->h;
  rect_nom_joueur->w = ((0.44*ecran.w)/17)*len_nom;
  rect_nom_joueur->h = rect_sprite_pv->h/2;
  if(num_joueur == 1){
    rect_nom_joueur->x = rect_sprite_pv->x;
  }else{
    rect_nom_joueur->x = (rect_sprite_pv->x+rect_sprite_pv->w)-rect_nom_joueur->w;
  }

  char * nom = joueur->perso.nom;
  SDL_Surface * surface = TTF_RenderText_Solid(font, nom, textColor);
  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

/**
 * @brief Fonction à appeler pour afficher les barres de vies apres l'init ( à utiliser pour redessiner la barre à chaque appel )
 * 
 * @param joueur Joueur auquel on va afficher le nom
 * @param rect_sprite_pv Rectangle de la partie grise de la barre de vie
 * @param texture_barre_de_vie Texture de la partie grise de la barre de vie
 * @param texture_carre_rouge Texture du carré rouge
 * @param texture_carre_jaune Texture du carré jaune
 * @param font Font à utiliser
 */
void barre_de_vie(Joueur * joueur, SDL_Rect * rect_sprite_pv, SDL_Texture * texture_barre_de_vie, SDL_Texture * texture_carre_rouge, SDL_Texture * texture_carre_jaune, TTF_Font* font){
    // SDL_rect de la barre de pv en fonction des pv
    SDL_Rect rect_pv,rect_pv_rouge,srcrect_pv_jaune;
    //destrect pv jaune
    rect_pv.y = rect_sprite_pv->y;
    if (joueur->vie != 0)
      rect_pv.w = (rect_sprite_pv->w/100.0)*joueur->vie;
    else
      rect_pv.w = 0;

    rect_pv.h = rect_sprite_pv->h ;
    rect_pv.x = rect_sprite_pv->x;
    //destrect pv rouge
    rect_pv_rouge.x = rect_sprite_pv->x;
    rect_pv_rouge.y = rect_sprite_pv->y;
    rect_pv_rouge.w = rect_sprite_pv->w;
    rect_pv_rouge.h = rect_sprite_pv->h;

    //srcrect pv jaune
    srcrect_pv_jaune.x =0;
    srcrect_pv_jaune.y =0;
    srcrect_pv_jaune.w =(1847/100)*joueur->vie;
    srcrect_pv_jaune.h =161;

    // creation rect rouge derriere le jaune
    SDL_RenderCopy(renderer, texture_carre_rouge, NULL ,&rect_pv_rouge );
    // creation rect jaune
    SDL_RenderCopy(renderer, texture_carre_jaune, &srcrect_pv_jaune ,&rect_pv );
    // sprite apres les rect de couleurs
    SDL_RenderCopy(renderer, texture_barre_de_vie, NULL, rect_sprite_pv);
}
