#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/jeu.h"
#include "../include/menu_selection.h"
#include "../include/animations.h"
#include "../include/map.h"
#include "../include/menu.h"

#define MODE BORDERLESS
bool quitter;

SDL_Window * window_menu;
SDL_Renderer * renderer_menu ;
SDL_Surface * image_stage_menu;
SDL_Rect srcBg, dstBg;
SDL_DisplayMode ecran;
SDL_Rect btn1, btn2, btn3, btn4;
SDL_Texture * texBtn1, * texBtn2, * texBtn3, * texBtn4;

SDL_Rect flamme1, flamme2, flamme3, flamme4;
SDL_Texture * texFlamme1, * texFlamme2, * texFlamme3, * texFlamme4;

int getSelection(int x_button, int y_button){
  if(x_button>(100.0/1920.0*ecran.w) && y_button>(50.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<50.0/1080.0*ecran.h+100.0))
    return 1;
  else if(x_button>(100.0/1920.0*ecran.w) && y_button>(150.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<150.0/1080.0*ecran.h+100.0))
    return 2;
  else if(x_button>(100.0/1920.0*ecran.w) && y_button>(250.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<250.0/1080.0*ecran.h+100.0))
    return 3;
  else if(x_button>(100.0/1920.0*ecran.w) && y_button>(350.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<350.0/1080.0*ecran.h+100.0))
    return 4;

  return 0;
}

  void initFlammes(SDL_Rect * rect, SDL_Texture ** texture, float x, float y){
    SDL_Surface * image_flamme_multi = IMG_Load("res/flamme.png");
    *texture = SDL_CreateTextureFromSurface(renderer_menu, image_flamme_multi);
    int text_width_flamme_multi = image_flamme_multi->w;
    int text_height_flamme_multi = image_flamme_multi->h;

    SDL_FreeSurface(image_flamme_multi);
    SDL_Rect rect_flamme_multi;
    rect_flamme_multi.x = x/1920.0*ecran.w;
    rect_flamme_multi.y = y/1080.0*ecran.h;
    rect_flamme_multi.w = text_width_flamme_multi+600.0;
    rect_flamme_multi.h = text_height_flamme_multi+50.0;

    *rect=rect_flamme_multi;
  }

  void renderMenu(int sortie){
    SDL_RenderClear(renderer_menu);
    jouerAnimationBackground(&srcBg, &dstBg,1);
    renderMap(&srcBg, &dstBg, renderer_menu);

    switch (sortie) {
      case 1: SDL_RenderCopy(renderer_menu, texFlamme1, NULL, &flamme1); break;
      case 2: SDL_RenderCopy(renderer_menu, texFlamme2, NULL, &flamme2); break;
      case 3: SDL_RenderCopy(renderer_menu, texFlamme3, NULL, &flamme3); break;
      case 4: SDL_RenderCopy(renderer_menu, texFlamme4, NULL, &flamme4); break;
    }

    SDL_RenderCopy(renderer_menu, texBtn1, NULL, &btn1);
    SDL_RenderCopy(renderer_menu, texBtn2, NULL, &btn2);
    SDL_RenderCopy(renderer_menu, texBtn3, NULL, &btn3);
    SDL_RenderCopy(renderer_menu, texBtn4, NULL, &btn4);

    SDL_RenderPresent(renderer_menu);
  }

  void menu_principal(){
    if(TTF_Init()==-1){
      printf("librairie non initialisé");
      exit(EXIT_FAILURE);
    }

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_GetDesktopDisplayMode(0, &ecran);

    switch(MODE){
      case FULLSCREEN:
        window_menu = SDL_CreateWindow("SDL2 Tekken - menu principal",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_FULLSCREEN);
        break;
      case BORDERLESS:
        window_menu = SDL_CreateWindow("SDL2 Tekken - menu principal",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_BORDERLESS);
        break;
    }

    renderer_menu = SDL_CreateRenderer(window_menu, -1, 0);
    chargerMap(0, renderer_menu,1);
  //preparation arriere plan texte
    //fond texte flamme multijoueur
    initFlammes(&flamme1, &texFlamme1, 75.0, 25.0);
    initFlammes(&flamme2, &texFlamme2, 75.0, 125.0);
    initFlammes(&flamme3, &texFlamme3, 75.0, 225.0);
    initFlammes(&flamme4, &texFlamme4, 75.0, 325.0);

  //preparation couleur et font du texte
    SDL_Color ColorWhite = {255, 255, 255, 0};
    int taille = 50;
    TTF_Font * font = TTF_OpenFont("res/fonts/Sans.ttf", taille);
    if (font == NULL) {
          fprintf(stderr, "error: font not found\n");
          printf("\n%s\n",TTF_GetError());
          exit(EXIT_FAILURE);
    }

    //création affichage jouer en multijoueur
    creerBouton(renderer_menu, font, "Jouer en multijoueur", ColorWhite, &btn1, &texBtn1, 75.0, 50.0);
    creerBouton(renderer_menu, font, "Jouer contre une IA", ColorWhite, &btn2, &texBtn2, 75.0, 150.0);
    creerBouton(renderer_menu, font, "Options", ColorWhite, &btn3, &texBtn3, 75.0, 250.0);
    creerBouton(renderer_menu, font, "Quitter", ColorWhite, &btn4, &texBtn4, 75.0, 350.0);

    //affichage du fond d'écran apres avoir néttoyer le renderer
   	int x_button;
  	int y_button;
    quitter=false;
    int sortie=1;

  while (!quitter) {
  	SDL_Event event;
  	//SDL_WaitEvent(&event);
  	SDL_PollEvent(&event);
    renderMenu(sortie);

  	switch (event.type){
  		case SDL_QUIT:
  			quitter = true;
  			break;
  		case SDL_MOUSEBUTTONDOWN:
  				x_button =event.button.x;
  				y_button =event.button.y;
          //sortie jouer en multijoueur

          switch (getSelection(x_button, y_button)) {
            case 1: quitter=true;
                    sortie=1;
                    break;
            case 2: quitter=true;
                    sortie=2;
                    break;
            case 3: quitter=true;
                    sortie=3;
                    break;
            case 4: quitter=true;
                    sortie=4;
                    break;
          }
  				break;

      case SDL_MOUSEMOTION:
        	x_button =event.button.x;
  				y_button =event.button.y;
      //postions de la souris
          //sur le texte multijoueur

          switch (getSelection(x_button, y_button)) {
            case 1:
                    sortie=1;
                    break;
            case 2:
                    sortie=2;
                    break;
            case 3:
                    sortie=3;
                    break;
            case 4:
                    sortie=4;
                    break;
          }
          break;

  		case SDL_KEYDOWN:
  		switch(event.key.keysym.sym){
  			case SDLK_q:
          quitter=true;
  			break;
  			case SDLK_RETURN :
        if(sortie){
          quitter=true;
        }
  			break;
        case SDLK_UP:
          if(sortie==0){
              sortie=1;
          }else if(sortie==2){
              sortie=1;
          }else if(sortie==3){
              sortie=2;
          }else if(sortie==4){
              sortie=3;
            }
  	break;
        case SDLK_DOWN:
          if(sortie==0){
              sortie=1;
          }else if(sortie==1){
              sortie=2;
          }else if(sortie==2){
              sortie=3;
          }else if(sortie==3){
              sortie=4;
  			  break;
        }
  		}
  	}
  }
    //fin du menu principal, changement de fenetre
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(texFlamme1);
    SDL_DestroyTexture(texFlamme2);
    SDL_DestroyTexture(texFlamme3);
    SDL_DestroyTexture(texFlamme4);
    SDL_DestroyTexture(texBtn1);
    SDL_DestroyTexture(texBtn2);
    SDL_DestroyTexture(texBtn3);
    SDL_DestroyTexture(texBtn4);
    SDL_DestroyRenderer(renderer_menu);
    SDL_DestroyWindow(window_menu);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    //redirection vers la sortie souhaité
    if(sortie==0){
      printf("\nerreur de sortie\n");
    }else if(sortie==1){
      printf("\nsortie 1: multijoueur\n");
    }else if(sortie==2){
      printf("\nsortie 2: IA\n");
      lancerMenu(MENU_SELECTION);
    }else if(sortie==3){
      printf("\nsortie 3 : options\n");
    }else if(sortie==4){
      printf("\nsortie 4 : quitter\n");
    }
  }
