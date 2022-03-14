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

#define MODE FULLSCREEN
bool quitter;

SDL_Window * window_menu;
SDL_Renderer * renderer_menu ;
SDL_Surface * image_stage_menu;
SDL_Rect srcBg, dstBg;
SDL_DisplayMode ecran;

  typedef struct {
    SDL_Texture * texture;
    SDL_Rect * rect;
  } texture_rect;

  void renderMenu(texture_rect texrect[], texture_rect flammes){
    int i;
    SDL_RenderClear(renderer_menu);
    jouerAnimationBackground(&srcBg, &dstBg);
    renderMap(&srcBg, &dstBg, renderer_menu);
    if(flammes.texture!=NULL)
      SDL_RenderCopy(renderer_menu, flammes.texture, NULL, flammes.rect);

    for(i=0; i<4; i++){
      SDL_RenderCopy(renderer_menu, texrect[i].texture, NULL, texrect[i].rect);
    }
    SDL_RenderPresent(renderer_menu);
  }

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

  void menu_principal(){
    texture_rect texrect[5];
    texture_rect flammes[5];

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
    chargerMap(0, renderer_menu);
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

    flammes[0].texture=texture_flamme_multi;
    flammes[0].rect=&rect_flamme_multi;

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

    flammes[1].texture=texture_flamme_IA;
    flammes[1].rect=&rect_flamme_IA;

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

    flammes[2].texture=texture_flamme_options;
    flammes[2].rect=&rect_flamme_options;

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

    flammes[3].texture=texture_flamme_quitter;
    flammes[3].rect=&rect_flamme_quitter;

  //preparation couleur et font du texte
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

    texrect[0].texture=texture_jouer_multi;
    texrect[0].rect=&rect_jouer_multi;

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

    texrect[1].texture=texture_jouer_IA;
    texrect[1].rect=&rect_jouer_IA;

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

    texrect[2].texture=texture_option;
    texrect[2].rect=&rect_option;

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

    texrect[3].texture=texture_quitter;
    texrect[3].rect=&rect_quitter;

    //affichage du fond d'écran apres avoir néttoyer le renderer
   	int x_button;
  	int y_button;
    quitter=false;
    int sortie=1;

  while (!quitter) {
  	SDL_Event event;
  	//SDL_WaitEvent(&event);
  	SDL_PollEvent(&event);
    renderMenu(texrect, flammes[sortie-1]);

  	switch (event.type){
  		case SDL_QUIT:
  			quitter = true;
        sortie=100;
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
    TTF_CloseFont(font);
    TTF_Quit();
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
