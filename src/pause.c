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

void selectionPause(SDL_Event * event){
    //  printf("buttons : %d, %d\n", x_button, y_button);

      switch (event->type){
        case SDL_QUIT:
        quit = true;
        break;

        case SDL_MOUSEBUTTONDOWN:
          x_button =event->button.x;
          y_button =event->button.y;
        //sortie jouer en multijoueur

        switch (getSelection(x_button, y_button, 100.0, 100.0, ecran.w/2)) {
          case 1: quit=true;
          sortie=1;
          break;
          case 2: quit=true;
          sortie=2;
          break;
          case 3: quit=true;
          sortie=3;
          break;
          case 4: quit=true;
          sortie=4;
          break;
        }
        break;
      }

      printf("sortie = %d\n", sortie);
      if(sortie<=1){
        //fin du menu principal, changement de fenetre
        SDL_RenderClear(renderer);
        SDL_DestroyTexture(texBtn1);
        SDL_DestroyTexture(texBtn2);
        SDL_DestroyTexture(texBtn3);
        SDL_DestroyTexture(texBtn4);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();

      } else {
          return;
      }
       if(sortie==2){
        lancerMenu(MENU_PRINCIPAL);
      }else if(sortie==3){
      }else if(sortie==4){
      }
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

  creerBouton(renderer, font, "Retour au combat", ColorWhite, &btn1, &texBtn1, ecran.w/2-btn1.w/2, ecran.h/4);
  creerBouton(renderer, font, "Retour au menu", ColorWhite, &btn2, &texBtn2, ecran.w/2-btn2.w/2, ecran.h/4+100);
  creerBouton(renderer, font, "Options", ColorWhite, &btn3, &texBtn3, ecran.w/2-btn3.w/2, ecran.h/4+200);
  creerBouton(renderer, font, "Quitter", ColorWhite, &btn4, &texBtn4, ecran.w/2-btn4.w/2, ecran.h/4+300);

  TTF_CloseFont(font);
  TTF_Quit();
}
