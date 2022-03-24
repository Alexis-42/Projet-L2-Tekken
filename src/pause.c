#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/jeu.h"
#include "../include/menu.h"
#include "../include/menu_principal.h"

SDL_Rect btn1, btn2, btn3, btn4, rectFinal;
SDL_Texture * texBtn1, * texBtn2, * texBtn3, * texBtn4;
int x_button, y_button, sortie=0;

void renderPause(){
  SDL_RenderCopy(renderer, texBtn1, NULL, &btn1);
  SDL_RenderCopy(renderer, texBtn2, NULL, &btn2);
  SDL_RenderCopy(renderer, texBtn3, NULL, &btn3);
  SDL_RenderCopy(renderer, texBtn4, NULL, &btn4);

  SDL_RenderPresent(renderer);
}

int getSelection2(int x_button, int y_button){
  if(x_button>(btn1.x/1920.0*ecran.w) && y_button>(50.0/1080.0*ecran.h) && x_button<(btn1.x/1920.0*ecran.w+600.0) && (y_button<50.0/1080.0*ecran.h+100.0))
    return 1;
  else if(x_button>(btn1.x/1920.0*ecran.w) && y_button>(150.0/1080.0*ecran.h) && x_button<(btn1.x/1920.0*ecran.w+600.0) && (y_button<150.0/1080.0*ecran.h+100.0))
    return 2;
  else if(x_button>(btn1.x/1920.0*ecran.w) && y_button>(250.0/1080.0*ecran.h) && x_button<(btn1.x/1920.0*ecran.w+600.0) && (y_button<250.0/1080.0*ecran.h+100.0))
    return 3;
  else if(x_button>(btn1.x/1920.0*ecran.w) && y_button>(350.0/1080.0*ecran.h) && x_button<(btn1.x/1920.0*ecran.w+600.0) && (y_button<350.0/1080.0*ecran.h+100.0))
    return 4;

  return 0;
}

void selectionPause(SDL_Event * event){
      switch (event->type){
        case SDL_MOUSEBUTTONDOWN:
          x_button =event->button.x;
          y_button =event->button.y;
        //sortie jouer en multijoueur
        break;
      }

      sortie = getSelection2(x_button, y_button);

      printf("sortie = %d\n", sortie);
      if(sortie==1){
          pause = false;
          sortie = 0;
      } else if(sortie==2){
         lancerMenu(MENU_PRINCIPAL);
         SDL_RenderClear(renderer);
         SDL_DestroyTexture(texBtn1);
         SDL_DestroyTexture(texBtn2);
         SDL_DestroyTexture(texBtn3);
         SDL_DestroyTexture(texBtn4);
         SDL_DestroyRenderer(renderer);
         SDL_DestroyWindow(window);
         SDL_Quit();
      }else if(sortie==3){
      } else if(sortie==4) quit=true;
}

void initPause(){
  SDL_Color ColorWhite = {255, 255, 255, 0};
  int taille=50;
  TTF_Font * font = TTF_OpenFont("res/fonts/Sans.ttf", taille);
  if (font == NULL) {
    fprintf(stderr, "error: font not found\n");
    printf("\n%s\n",TTF_GetError());
    exit(EXIT_FAILURE);
  }
  int x = 720;
  creerBouton(renderer, font, "Retour au combat", ColorWhite, &btn1, &texBtn1, x/1920.0*ecran.w, 50/1920.0*ecran.w);
  creerBouton(renderer, font, "Retour au menu", ColorWhite, &btn2, &texBtn2, x/1920.0*ecran.w, 150/1920.0*ecran.w);
  creerBouton(renderer, font, "Options", ColorWhite, &btn3, &texBtn3, x/1920.0*ecran.w, 250/1920.0*ecran.w);
  creerBouton(renderer, font, "Quitter", ColorWhite, &btn4, &texBtn4, x/1920.0*ecran.w, 350/1920.0*ecran.w);

  TTF_CloseFont(font);
  TTF_Quit();
}
