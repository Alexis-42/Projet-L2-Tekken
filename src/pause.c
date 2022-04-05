/**
 * @file pause.c
 * @author Notelet Léo, Pecquery Charly, Guimbert Alexis
 * @brief fichier qui gère le menu pause
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/jeu.h"
#include "../include/menu.h"

#define POSX_TEXTE 720.0/1920.0*ecran.w+100.0
SDL_Rect btn1, btn2, btn3, btn4, rectbackground;
SDL_Texture * texBtn1, * texBtn2, * texBtn3, * texBtn4;
int sortie=0;

/**
 * @brief fonction d'affichage du menu pause 
 * 
 */
void renderPause(){
  SDL_RenderFillRect(renderer, &rectbackground);
  SDL_RenderCopy(renderer, texBtn1, NULL, &btn1);
  SDL_RenderCopy(renderer, texBtn2, NULL, &btn2);
  SDL_RenderCopy(renderer, texBtn3, NULL, &btn3);
}

/**
 * @brief vérifie l'emplacement de la souris et retourne une valeur en fonction de cette emplacement
 * 
 * @param x_button coordonné x de la souris 
 * @param y_button coordonné y de la souris
 * @return int valeur lié à l'emplacement de la souris
 */
int getSelection2(int x_button, int y_button){
  if(x_button>btn1.x && y_button>btn1.y && x_button<btn1.x+600.0 && y_button<btn1.y+50.0)
    return 1;
  else if(x_button>btn2.x && y_button>btn2.y && x_button<btn2.x+600.0 && y_button<btn2.y+50.0)
    return 2;
  else if(x_button>btn3.x && y_button>btn3.y && x_button<btn3.x+600.0 && y_button<btn3.y+50.0)
    return 3;

  return 0;
}

/**
 * @brief fonction qui supprime l'affichage du menu pause et qui fait quitter le jeu
 * 
 */
void quitter2(){
  SDL_DestroyTexture(texBtn1);
  SDL_DestroyTexture(texBtn2);
  SDL_DestroyTexture(texBtn3);
  SDL_DestroyTexture(texBtn4);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  quit = true;
}

/**
 * @brief fonction qui gère la sortie du menu pause
 * 
 * @param event structure des évenements de la souris
 * @param drip option d'affichage
 * @param ia variable qui vérifie si l'on est en joueur contre joueur ou en  joueur contre IA
 */
void selectionPause(SDL_Event event, int drip, int ia){
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
         quitter2();
      }else if(sortie==3){
        quitter2();
      }
}

/**
 * @brief fonction qui initialise le menu pause pour pouvoir l'utiliser après sans problème
 * 
 */
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

  creerBouton(font, "Retour au combat", ColorWhite, &btn1, &texBtn1, POSX_TEXTE/1920.0*ecran.w, 300/1920.0*ecran.w);
  creerBouton(font, "Retour au menu", ColorWhite, &btn2, &texBtn2, POSX_TEXTE/1920.0*ecran.w, 400/1920.0*ecran.w);
  creerBouton(font, "Quitter", ColorWhite, &btn3, &texBtn3, POSX_TEXTE/1920.0*ecran.w, 500/1920.0*ecran.w);
}