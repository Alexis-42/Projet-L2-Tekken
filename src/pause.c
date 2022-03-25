#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/jeu.h"
#include "../include/menu.h"

#define POSX_TEXTE 720.0
SDL_Rect btn1, btn2, btn3, btn4, rectbackground;
SDL_Texture * texBtn1, * texBtn2, * texBtn3, * texBtn4;
int sortie=0;

void renderPause(){
  SDL_RenderFillRect(renderer, &rectbackground);
  SDL_RenderCopy(renderer, texBtn1, NULL, &btn1);
  SDL_RenderCopy(renderer, texBtn2, NULL, &btn2);
  SDL_RenderCopy(renderer, texBtn3, NULL, &btn3);
  SDL_RenderCopy(renderer, texBtn4, NULL, &btn4);
}

int getSelection2(int x_button, int y_button){
  if(x_button>(POSX_TEXTE/1920.0*ecran.w) && y_button>(201.0/1080.0*ecran.h) && x_button<(POSX_TEXTE/1920.0*ecran.w+600.0) && (y_button<300.0/1080.0*ecran.h+100.0))
    return 1;
  else if(x_button>(POSX_TEXTE/1920.0*ecran.w) && y_button>(301.0/1080.0*ecran.h) && x_button<(POSX_TEXTE/1920.0*ecran.w+600.0) && (y_button<400.0/1080.0*ecran.h+100.0))
    return 2;
  else if(x_button>(POSX_TEXTE/1920.0*ecran.w) && y_button>(401.0/1080.0*ecran.h) && x_button<(POSX_TEXTE/1920.0*ecran.w+600.0) && (y_button<500.0/1080.0*ecran.h+100.0))
    return 3;
  else if(x_button>(POSX_TEXTE/1920.0*ecran.w) && y_button>(501.0/1080.0*ecran.h) && x_button<(POSX_TEXTE/1920.0*ecran.w+600.0) && (y_button<600.0/1080.0*ecran.h+100.0))
    return 4;

  return 0;
}

void quitterr(){
  SDL_DestroyTexture(texBtn1);
  SDL_DestroyTexture(texBtn2);
  SDL_DestroyTexture(texBtn3);
  SDL_DestroyTexture(texBtn4);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  quit = true;
}

void selectionPause(SDL_Event event){
      switch (event.type){
        case SDL_MOUSEBUTTONDOWN:
          sortie = getSelection2(event.button.x, event.button.y);
        //sortie jouer en multijoueur
        break;
      }
      
      if(sortie==1){
          sortie = 0;
          pause = false;
      } else if(sortie==2){
         quitterr();
         lancerMenu(MENU_PRINCIPAL);
      }else if(sortie==3){
      } else if(sortie==4) {
        quitterr();
      };
}

void initPause(){
  sortie=0;
  pause=false;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_Color ColorWhite = {255, 255, 255, 0};
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
  int taille=50;
  TTF_Font * font = TTF_OpenFont("res/fonts/Sans.ttf", taille);
  if (font == NULL) {
    fprintf(stderr, "error: font not found\n");
    printf("\n%s\n",TTF_GetError());
    exit(EXIT_FAILURE);
  }

  rectbackground.w = ecran.w;
  rectbackground.h = ecran.h;

  creerBouton(renderer, font, "Retour au combat", ColorWhite, &btn1, &texBtn1, POSX_TEXTE/1920.0*ecran.w, 300/1920.0*ecran.w);
  creerBouton(renderer, font, "Retour au menu", ColorWhite, &btn2, &texBtn2, POSX_TEXTE/1920.0*ecran.w, 400/1920.0*ecran.w);
  creerBouton(renderer, font, "Options", ColorWhite, &btn3, &texBtn3, POSX_TEXTE/1920.0*ecran.w, 500/1920.0*ecran.w);
  creerBouton(renderer, font, "Quitter", ColorWhite, &btn4, &texBtn4, POSX_TEXTE/1920.0*ecran.w, 600/1920.0*ecran.w);
}