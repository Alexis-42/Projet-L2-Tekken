#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/animations.h"
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/personnages.h"
#include "../include/map.h"
#define OFFSET 26
SDL_DisplayMode ecran;

void renderAnimation(Joueur * joueur){
  SDL_RenderCopyEx(renderer, (joueur->texture), &(joueur->perso.srcrect), &(joueur->perso.dstrect), 0, 0, joueur->direction);
}


void init_affichage_temps(int sec_deb_combat, TTF_Font* font, SDL_Renderer * renderer, SDL_Rect * rect_sprite_pvj1){
  char str_temps[3];
  SDL_Color textColor = {255, 255, 255, 0};
  SDL_Rect rect_temps;
  rect_temps.x = rect_sprite_pvj1->x+rect_sprite_pvj1->w;
  rect_temps.y = rect_sprite_pvj1->y; 
  rect_temps.w = ecran.w-(2*rect_sprite_pvj1->w);
  rect_temps.h = rect_sprite_pvj1->h;
  snprintf(str_temps, sizeof(str_temps), "%i", 60-sec_deb_combat);

  SDL_Surface * surface = TTF_RenderText_Solid(font, str_temps, textColor);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL ,&rect_temps);
  SDL_DestroyTexture(texture);
}

// fonction qui permet l'init d'un sprite barre de vie en fonction du joueur
void init_sprite_pv(SDL_Rect * rect_sprite_pv, int num_joueur){
  rect_sprite_pv->y = 0;
  rect_sprite_pv->w = 854;
  rect_sprite_pv->h = 161;
  if(num_joueur==1){
    rect_sprite_pv->x = 0;
  }else{
    rect_sprite_pv->x = ecran.w-rect_sprite_pv->w ;
  }
}

// fonction à appeler pour afficher les barres de vies apres l'init ( à utiliser pour redessiner la barre à chaque appel )
void barre_de_vie(Joueur * joueur, SDL_Rect * rect_sprite_pv, SDL_Surface * sprite_barre_de_vie, SDL_Renderer * renderer, int num_joueur){
    // SDL_rect de la barre de pv en fonction des pv
    SDL_Rect rect_pv,rect_pv_rouge;
    //destrect pv rouge
    rect_pv.y = 0;
    if (joueur->vie != 0){
      rect_pv.w = (rect_sprite_pv->w/100)*joueur->vie;
    }
    else
      rect_pv.w = 0;
    rect_pv.h = rect_sprite_pv->h ;
    if(num_joueur==1){
      rect_pv.x = OFFSET;
    }else{
      rect_pv.x = rect_sprite_pv->x+OFFSET;
    }
    //destrect pv jaune
    rect_pv_rouge.x = rect_pv.x;
    rect_pv_rouge.y = rect_pv.y ;
    rect_pv_rouge.w = rect_sprite_pv->w-(OFFSET *2);
    rect_pv_rouge.h = rect_sprite_pv->h;

    // creation rect rouge derriere le jaune
    SDL_Surface * image_carre_rouge = IMG_Load("res/carre_rouge.png");
    SDL_Texture * texture_carre_rouge = SDL_CreateTextureFromSurface(renderer, image_carre_rouge);
    SDL_FreeSurface(image_carre_rouge);
    SDL_RenderCopy(renderer, texture_carre_rouge, NULL ,&rect_pv_rouge );
    SDL_DestroyTexture(texture_carre_rouge);

    // creation rect jaune
    SDL_Surface * image_carre_jaune = IMG_Load("res/carre_jaune.png");
    SDL_Texture * texture_carre_jaune = SDL_CreateTextureFromSurface(renderer, image_carre_jaune);
    SDL_FreeSurface(image_carre_jaune);
    SDL_RenderCopy(renderer, texture_carre_jaune, NULL ,&rect_pv );
    SDL_DestroyTexture(texture_carre_jaune);

    // sprite apres les rect de couleurs
    SDL_Texture * texture_barre_de_vie = SDL_CreateTextureFromSurface(renderer, sprite_barre_de_vie);
    SDL_RenderCopy(renderer, texture_barre_de_vie, NULL, rect_sprite_pv);
    SDL_DestroyTexture(texture_barre_de_vie);
}

void resetAnimation(Joueur * joueur){
  joueur->perso.frame=0;
  SDL_Rect srcrect = {
    0, //Pas
    0,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };

  SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };
  joueur->perso.srcrect=srcrect;
  joueur->perso.dstrect=dstrect;
}

void jouerAnimation(Joueur * joueur){
  int posYSprite;
  int anim=joueur->action;

  switch (anim) {
    case COURIR: posYSprite=0;
    break;
    case PARER: posYSprite=640;
    break;
    case POING: posYSprite=1280;
    break;
    case IDLE: posYSprite=0;
  }
  Uint32 seconds = SDL_GetTicks() / 30; //Fréquence (toutes les 30ms)

  if(anim!=COURIR){
  if(joueur->perso.frame-1<joueur->perso.nb_frame[anim]){
    if(joueur->perso.seconds!=seconds){

    SDL_Rect srcrect = {
    joueur->perso.frame * 540, //Pas
    posYSprite,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };

  SDL_Rect dstrect = {
    joueur->position.x,
    joueur->position.y,
    joueur->perso.taille_perso.w,
    joueur->perso.taille_perso.h
  };
   joueur->perso.srcrect=srcrect;
   joueur->perso.dstrect=dstrect;

      joueur->perso.frame++;
      joueur->perso.seconds=seconds;
    }
  }
} else {
  SDL_Rect srcrect = {
  (seconds%joueur->perso.nb_frame[anim]) * 540, //Pas
  posYSprite,
  joueur->perso.taille_perso.w,
  joueur->perso.taille_perso.h
};

SDL_Rect dstrect = {
  joueur->position.x,
  joueur->position.y,
  joueur->perso.taille_perso.w,
  joueur->perso.taille_perso.h
};
 joueur->perso.srcrect=srcrect;
 joueur->perso.dstrect=dstrect;

    joueur->perso.frame++;
    joueur->perso.seconds=seconds;
}
}

void jouerAnimationBackground(SDL_Rect * srcBg, SDL_Rect * dstBg){
  Uint32 seconds = SDL_GetTicks() / 100; //Fréquence (toutes les 100ms)
  Uint32 sprite = seconds % nbFramesMap;

    SDL_Rect srcrect = {
    sprite * pas,
    0,
    726,
    368
  };

  SDL_Rect dstrect = {
    0,
    0,
    ecran.w,
    ecran.h
  };
   *srcBg=srcrect;
   *dstBg=dstrect;
}
