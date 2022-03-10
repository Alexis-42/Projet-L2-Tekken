#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/jeu.h"
#include "../include/menu_selection.h"

  bool quitter;

  SDL_Window * window_menu;
  SDL_Renderer * renderer_menu ;
  SDL_Surface * image_stage_menu;
  SDL_Texture * texture_stage_menu;

  SDL_DisplayMode ecran;

  void menu_principal(){


    if(TTF_Init()==-1){
      printf("librairie non initialisé");
      exit(EXIT_FAILURE);
    }

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_GetDesktopDisplayMode(0, &ecran);

    SDL_Window * window_menu = SDL_CreateWindow("SDL2 Tekken - menu principal",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_BORDERLESS);
    SDL_Renderer * renderer_menu = SDL_CreateRenderer(window_menu, -1, 0);
    SDL_Surface * image_stage_menu = IMG_Load("res/backgrounds/ryu_menu.png");
    SDL_Texture * texture_stage_menu = SDL_CreateTextureFromSurface(renderer_menu, image_stage_menu);
  //preparation arriere plan texte
    //fond texte flamme multijoueur
    SDL_Surface * image_flamme_multi = IMG_Load("res/flamme3.png");
    SDL_Texture * texture_flamme_multi = SDL_CreateTextureFromSurface(renderer_menu, image_flamme_multi);
    int text_width_flamme_multi = image_flamme_multi->w;
    int text_height_flamme_multi = image_flamme_multi->h;

    SDL_FreeSurface(image_flamme_multi);
    SDL_Rect rect_flamme_multi;
    rect_flamme_multi.x = 75.0/1920.0*ecran.w;
    rect_flamme_multi.y = 25.0/1080.0*ecran.h;
    rect_flamme_multi.w = text_width_flamme_multi+600.0;
    rect_flamme_multi.h = text_height_flamme_multi+50.0;

    //fond flamme texte IA
    SDL_Surface * image_flamme_IA = IMG_Load("res/flamme3.png");
    SDL_Texture * texture_flamme_IA = SDL_CreateTextureFromSurface(renderer_menu, image_flamme_IA);
    int text_width_flamme_IA = image_flamme_IA->w;
    int text_height_flamme_IA = image_flamme_IA->h;

    SDL_FreeSurface(image_flamme_IA);
    SDL_Rect rect_flamme_IA;
    rect_flamme_IA.x = 75.0/1920.0*ecran.w;
    rect_flamme_IA.y = 125.0/1080.0*ecran.h;
    rect_flamme_IA.w = text_width_flamme_IA+600.0;
    rect_flamme_IA.h = text_height_flamme_IA+50.0;

    //fond flamme texte options
    SDL_Surface * image_flamme_options = IMG_Load("res/flamme3.png");
    SDL_Texture * texture_flamme_options = SDL_CreateTextureFromSurface(renderer_menu, image_flamme_options);
    int text_width_flamme_options = image_flamme_options->w;
    int text_height_flamme_options = image_flamme_options->h;

    SDL_FreeSurface(image_flamme_options);
    SDL_Rect rect_flamme_options;
    rect_flamme_options.x = 75.0/1920.0*ecran.w;
    rect_flamme_options.y = 225.0/1080.0*ecran.h;
    rect_flamme_options.w = text_width_flamme_options+250.0;
    rect_flamme_options.h = text_height_flamme_options+50.0;


    //fond flamme texte quitter
    SDL_Surface * image_flamme_quitter = IMG_Load("res/flamme3.png");
    SDL_Texture * texture_flamme_quitter = SDL_CreateTextureFromSurface(renderer_menu, image_flamme_quitter);
    int text_width_flamme_quitter = image_flamme_quitter->w;
    int text_height_flamme_quitter = image_flamme_quitter->h;

    SDL_FreeSurface(image_flamme_quitter);
    SDL_Rect rect_flamme_quitter;
    rect_flamme_quitter.x = 75.0/1920.0*ecran.w;
    rect_flamme_quitter.y = 325.0/1080.0*ecran.h;
    rect_flamme_quitter.w = text_width_flamme_quitter+250.0;
    rect_flamme_quitter.h = text_height_flamme_quitter+50.0;

  //preparation couleur et font du texte
    SDL_Color ColorRed = {255, 0, 0, 0};
    SDL_Color ColorWhite = {255, 255, 255, 0};
    int taille = 50;
    TTF_Font * font = TTF_OpenFont("res/fonts/Sans.ttf", taille);
    if (font == NULL) {
          fprintf(stderr, "error: font not found\n");
          printf("\n%s\n",TTF_GetError());
          exit(EXIT_FAILURE);
    }


    //affichage menu principal

    //création affichage jouer en multijoueur
    SDL_Surface * surface_jouer_multi = TTF_RenderText_Solid(font,"jouer en multijoueur", ColorWhite);
    SDL_Texture * texture_jouer_multi = SDL_CreateTextureFromSurface(renderer_menu, surface_jouer_multi);
    int text_width_jouer_multi = surface_jouer_multi->w;
    int text_height_jouer_multi = surface_jouer_multi->h;

    SDL_FreeSurface(surface_jouer_multi);
    SDL_Rect rect_jouer_multi;

    rect_jouer_multi.x = 100.0/1920.0*ecran.w;
    rect_jouer_multi.y = 50.0/1080.0*ecran.h;
    rect_jouer_multi.w = text_width_jouer_multi;
    rect_jouer_multi.h = text_height_jouer_multi;

    //création affichage jouer contre IA
    SDL_Surface * surface_jouer_IA = TTF_RenderText_Solid(font,"jouer contre une IA", ColorWhite);
    SDL_Texture * texture_jouer_IA = SDL_CreateTextureFromSurface(renderer_menu, surface_jouer_IA);

    int text_width_jouer_IA = surface_jouer_IA->w;
    int text_height_jouer_IA = surface_jouer_IA->h;
    SDL_FreeSurface(surface_jouer_IA);

    SDL_Rect rect_jouer_IA;
    rect_jouer_IA.x = 100.0/1920.0*ecran.w;
    rect_jouer_IA.y = 150.0/1080.0*ecran.h;;
    rect_jouer_IA.w = text_width_jouer_IA;
    rect_jouer_IA.h = text_height_jouer_IA;


    //création affichage option
    SDL_Surface * surface_option = TTF_RenderText_Solid(font,"options", ColorWhite);
    SDL_Texture * texture_option = SDL_CreateTextureFromSurface(renderer_menu, surface_option);

    int text_width_option = surface_option->w;
    int text_height_option = surface_option->h;
    SDL_FreeSurface(surface_option);

    SDL_Rect rect_option;
    rect_option.x = 100.0/1920.0*ecran.w;
    rect_option.y = 250.0/1080.0*ecran.h;;
    rect_option.w = text_width_option;
    rect_option.h = text_height_option;


    //création affichage quitter
    SDL_Surface * surface_quitter = TTF_RenderText_Solid(font,"quitter", ColorWhite);
    SDL_Texture * texture_quitter = SDL_CreateTextureFromSurface(renderer_menu, surface_quitter);

    int text_width_quitter = surface_quitter->w;
    int text_height_quitter = surface_quitter->h;
    SDL_FreeSurface(surface_quitter);

    SDL_Rect rect_quitter;
    rect_quitter.x = 100.0/1920.0*ecran.w;
    rect_quitter.y = 350.0/1080.0*ecran.h;;
    rect_quitter.w = text_width_quitter;
    rect_quitter.h = text_height_quitter;



    //affichage du fond d'écran apres avoir néttoyer le renderer
    SDL_RenderClear(renderer_menu);
    SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);

    /* texture des flammes
    SDL_RenderCopy(renderer_menu, texture_flamme_multi, NULL, &rect_flamme_multi);
    SDL_RenderCopy(renderer_menu, texture_flamme_IA, NULL, &rect_flamme_IA);
    SDL_RenderCopy(renderer_menu, texture_flamme_options, NULL, &rect_flamme_options);
    SDL_RenderCopy(renderer_menu, texture_flamme_quitter, NULL, &rect_flamme_quitter);*/


    //affichage des textes
    SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
    SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
    SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
    SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
    //affichage du tout
    SDL_RenderPresent(renderer_menu);

   	int x_button;
  	int y_button;
    quitter=false;
    int sortie=0;

  while (!quitter) {
  	SDL_Event event;
  	SDL_WaitEvent(&event);
  	//SDL_PollEvent(&event);
  	switch (event.type){
  		case SDL_QUIT:
  			quitter = true;
        sortie=100;
  			break;
  		case SDL_MOUSEBUTTONDOWN:
  				x_button =event.button.x;
  				y_button =event.button.y;
  				printf("\n%i %i",x_button,y_button);
          //sortie jouer en multijoueur
          if(x_button>(100.0/1920.0*ecran.w) && y_button>(50.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<50.0/1080.0*ecran.h+100.0)){
            quitter=true;
            sortie=1;
          }
          //sortie contre IA
          if(x_button>(100.0/1920.0*ecran.w) && y_button>(150.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<150.0/1080.0*ecran.h+100.0)){
            quitter=true;
            sortie=2;
          }
          //sortie option
          if(x_button>(100.0/1920.0*ecran.w) && y_button>(250.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<250.0/1080.0*ecran.h+100.0)){
            quitter=true;
            sortie=3;
          }
          //sortie quitter
          if(x_button>(100.0/1920.0*ecran.w) && y_button>(350.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<350.0/1080.0*ecran.h+100.0)){
            quitter=true;
            sortie=4;
          }
  				break;

      case SDL_MOUSEMOTION:
        	x_button =event.button.x;
  				y_button =event.button.y;
      //postions de la souris
          //sur le texte multijoueur
          if(x_button>(100.0/1920.0*ecran.w) && y_button>(50.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<50.0/1080.0*ecran.h+100.0)){
              printf("\nsouris sur 1");
                  sortie=1;
                  SDL_RenderClear(renderer_menu);
                  SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
                  SDL_RenderCopy(renderer_menu, texture_flamme_multi, NULL, &rect_flamme_multi);
                  SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
                  SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
                  SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
                  SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
                  SDL_RenderPresent(renderer_menu);
          }
          //sur le texte contre IA
          else if(x_button>(100.0/1920.0*ecran.w) && y_button>(150.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<150.0/1080.0*ecran.h+100.0)){
              printf("\nsouris sur 2");
                  sortie=2;
                  SDL_RenderClear(renderer_menu);
                  SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
                  SDL_RenderCopy(renderer_menu, texture_flamme_IA, NULL, &rect_flamme_IA);
                  SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
                  SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
                  SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
                  SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
                  SDL_RenderPresent(renderer_menu);
          }
          //sur le texte options
          else if(x_button>(100.0/1920.0*ecran.w) && y_button>(250.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<250.0/1080.0*ecran.h+100.0)){
              printf("\nsouris sur 3");
                  sortie=3;
                  SDL_RenderClear(renderer_menu);
                  SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
                  SDL_RenderCopy(renderer_menu, texture_flamme_options, NULL, &rect_flamme_options);
                  SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
                  SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
                  SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
                  SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
                  SDL_RenderPresent(renderer_menu);
          }
          //sur le texte quitter
          else if(x_button>(100.0/1920.0*ecran.w) && y_button>(350.0/1080.0*ecran.h) && x_button<(100.0/1920.0*ecran.w+600.0) && (y_button<350.0/1080.0*ecran.h+100.0)){
              printf("\nsouris sur 4");
                  sortie=4;
                  SDL_RenderClear(renderer_menu);
                  SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
                  SDL_RenderCopy(renderer_menu, texture_flamme_quitter, NULL, &rect_flamme_quitter);
                  SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
                  SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
                  SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
                  SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
                  SDL_RenderPresent(renderer_menu);
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
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_multi, NULL, &rect_flamme_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
          }else if(sortie==2){
              sortie=1;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_multi, NULL, &rect_flamme_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
          }else if(sortie==3){
              sortie=2;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_IA, NULL, &rect_flamme_IA);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);

          }else if(sortie==4){
              sortie=3;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_options, NULL, &rect_flamme_options);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
            }
  			break;
        case SDLK_DOWN:
          if(sortie==0){
              sortie=1;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_multi, NULL, &rect_flamme_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
          }else if(sortie==1){
              sortie=2;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_IA, NULL, &rect_flamme_IA);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
          }else if(sortie==2){
              sortie=3;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_options, NULL, &rect_flamme_options);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
          }else if(sortie==3){
              sortie=4;
              SDL_RenderClear(renderer_menu);
              SDL_RenderCopy(renderer_menu, texture_stage_menu, NULL, NULL);
              SDL_RenderCopy(renderer_menu, texture_flamme_quitter, NULL, &rect_flamme_quitter);
              SDL_RenderCopy(renderer_menu,texture_jouer_multi, NULL, &rect_jouer_multi);
              SDL_RenderCopy(renderer_menu,texture_jouer_IA, NULL, &rect_jouer_IA);
              SDL_RenderCopy(renderer_menu,texture_option, NULL, &rect_option);
              SDL_RenderCopy(renderer_menu,texture_quitter, NULL, &rect_quitter);
              SDL_RenderPresent(renderer_menu);
  			  break;
        }
  		}
  	}
  }
    //fin du menu principal, changement de fenetre
    SDL_DestroyTexture(texture_flamme_IA);
    SDL_DestroyTexture(texture_flamme_multi);
    SDL_DestroyTexture(texture_flamme_options);
    SDL_DestroyTexture(texture_flamme_quitter);
    SDL_DestroyTexture(texture_jouer_multi);
    SDL_DestroyTexture(texture_jouer_IA);
    SDL_DestroyTexture(texture_option);
    SDL_DestroyTexture(texture_quitter);
    SDL_DestroyRenderer(renderer_menu);
    SDL_DestroyWindow(window_menu);
    IMG_Quit();
    SDL_Quit();

    //redirection vers la sortie souhaité
    if(sortie==0){
      printf("\nerreur de sortie\n");
    }else if(sortie==1){
      printf("\nsortie 1: multijoueur\n");
      initSdl();
    }else if(sortie==2){
      printf("\nsortie 2: IA\n");
      menu_selection();
    }else if(sortie==3){
      printf("\nsortie 3 : options\n");
    }else if(sortie==4){
      printf("\nsortie 4 : quitter\n");
    }
  }
