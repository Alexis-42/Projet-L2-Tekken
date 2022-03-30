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
#include "../include/options.h"

bool quitter;
SDL_Surface * image_stage_menu;
SDL_Surface * surface_jonathan;
SDL_Rect srcBg, dstBg;
SDL_DisplayMode ecran;
SDL_Rect btn1, btn2, btn3, btn4;
SDL_Texture * texBtn1, * texBtn2, * texBtn3, * texBtn4, * texture_jonathan;

SDL_Rect flamme1, flamme2, flamme3, flamme4;
SDL_Texture * texFlamme1, * texFlamme2, * texFlamme3, * texFlamme4;

int debug;
int difficulte;
int modeAffichage = BORDERLESS;
int nbreRoundsMax;

void renderjonathan(SDL_Renderer * renderer, int drip){
  if(drip){
    // photo jonathan
    SDL_Rect rect_jonathan={ecran.w-213, 0, 213, 317};
    surface_jonathan = IMG_Load("res/jonathan.png");
    texture_jonathan = SDL_CreateTextureFromSurface(renderer, surface_jonathan);
    SDL_FreeSurface(surface_jonathan);
    SDL_RenderCopy(renderer, texture_jonathan, NULL, &rect_jonathan);
    SDL_DestroyTexture(texture_jonathan);
  }
}

int getSelection(int x_button, int y_button){
  if(x_button>btn1.x && y_button>btn1.y && x_button<btn1.x+600.0 && y_button<btn1.y+100.0)
    return 1;
  else if(x_button>btn2.x && y_button>btn2.y && x_button<btn2.x+600.0 && y_button<btn2.y+100.0)
    return 2;
  else if(x_button>btn3.x && y_button>btn3.y && x_button<btn3.x+600.0 && y_button<btn3.y+100.0)
    return 3;
  else if(x_button>btn4.x && y_button>btn4.y && x_button<btn4.x+600.0 && y_button<btn4.y+100.0)
    return 4;

  return 0;
}

  void renderMenu(int sortie, int drip){
    SDL_RenderClear(renderer);
    
    jouerAnimationBackground(&srcBg, &dstBg,1);
    renderMap(&srcBg, &dstBg, renderer);

    renderjonathan(renderer,drip);

    switch (sortie) {
      case 1: SDL_RenderCopy(renderer, texFlamme1, NULL, &flamme1); break;
      case 2: SDL_RenderCopy(renderer, texFlamme2, NULL, &flamme2); break;
      case 3: SDL_RenderCopy(renderer, texFlamme3, NULL, &flamme3); break;
      case 4: SDL_RenderCopy(renderer, texFlamme4, NULL, &flamme4); break;
    }

    SDL_RenderCopy(renderer, texBtn1, NULL, &btn1);
    SDL_RenderCopy(renderer, texBtn2, NULL, &btn2);
    SDL_RenderCopy(renderer, texBtn3, NULL, &btn3);
    SDL_RenderCopy(renderer, texBtn4, NULL, &btn4);

    SDL_RenderPresent(renderer);
  }

  void menu_principal(int drip){
    if(TTF_Init()==-1){
      printf("librairie non initialisé");
      exit(EXIT_FAILURE);
    }

   SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  SDL_GetDesktopDisplayMode(0, &ecran);

  switch(modeAffichage){
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

  chargerMap(0, renderer,1,drip);
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

    FILE * fichier_prefs = chargerFichierPref("options");
    chargerPreferences(fichier_prefs);

    //création affichage jouer en multijoueur
    creerBouton(font, "Jouer en multijoueur", ColorWhite, &btn1, &texBtn1, 75.0, 50.0);
    creerBouton(font, "Jouer contre une IA", ColorWhite, &btn2, &texBtn2, 75.0, 150.0);
    creerBouton(font, "Options", ColorWhite, &btn3, &texBtn3, 75.0, 250.0);
    creerBouton(font, "Quitter", ColorWhite, &btn4, &texBtn4, 75.0, 350.0);

    //affichage du fond d'écran apres avoir néttoyer le renderer
   	int x_button;
  	int y_button;
    quitter=false;
    int sortie=1;

  while (!quitter) {
  	SDL_Event event;
  	//SDL_WaitEvent(&event);
  	SDL_PollEvent(&event);
    renderMenu(sortie, drip);

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
    TTF_CloseFont(font);
    TTF_Quit();

    //redirection vers la sortie souhaité
    if(sortie==0){
      printf("\nerreur de sortie\n");
    }else if(sortie==1){
      printf("\nsortie 1: multijoueur local\n");
      lancerMenu(MENU_SELECTION, drip, 0);
    }else if(sortie==2){
      printf("\nsortie 2: IA\n");
      lancerMenu(MENU_SELECTION, drip, 1);
    }else if(sortie==3){
      printf("\nsortie 3 : options\n");
      lancerMenu(MENU_OPTIONS, drip, 0);
    }else if(sortie==4){
      printf("\nsortie 4 : quitter\n");
    }
  }
