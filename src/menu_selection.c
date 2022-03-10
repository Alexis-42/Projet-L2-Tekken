#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/menu_principal.h"
#include "../include/jeu.h"

void menu_selection(){

//initialisation de sdl
    if(TTF_Init()==-1){
      printf("librairie non initialisé");
      exit(EXIT_FAILURE);
    }
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

//création de la page
    SDL_Window * window_menu_selection = SDL_CreateWindow("SDL2 Tekken - menu selection personnage",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, 0);
    SDL_Renderer * renderer_menu_selection = SDL_CreateRenderer(window_menu_selection, -1, 0);
    SDL_Surface * image_stage_menu_selection = IMG_Load("res/backgrounds/ryu_menu.png");
    SDL_Texture * texture_stage_menu_selection = SDL_CreateTextureFromSurface(renderer_menu_selection, image_stage_menu_selection);

//preparation image des personnages
    //image de shrek
    SDL_Surface * image_shrek = IMG_Load("res/shrek.png");
    SDL_Texture * texture_shrek = SDL_CreateTextureFromSurface(renderer_menu_selection, image_shrek);
    int text_width_shrek = image_shrek->w;
    int text_height_shrek = image_shrek->h;

    SDL_FreeSurface(image_shrek);
    SDL_Rect rect_shrek;
    rect_shrek.x = 100.0/1920.0*ecran.w;
    rect_shrek.y = 50.0/1080.0*ecran.h;
    rect_shrek.w = text_width_shrek;
    rect_shrek.h = text_height_shrek;

//affichage de la page
    SDL_RenderClear(renderer_menu_selection);
    SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
    SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
    SDL_RenderPresent(renderer_menu_selection);

//recherche des actions
    bool quitter=false;
    while (!quitter) {
        SDL_Event event;
  	    SDL_WaitEvent(&event);
    	switch (event.type){
  	    	case SDL_QUIT:
  	    		quitter = true;
  	    		break;
            case SDL_KEYDOWN:
  		        switch(event.key.keysym.sym){
  			        case SDLK_q:
                        quitter=true;
  			    break;
                }
        }
    }


    SDL_DestroyRenderer(renderer_menu_selection);
    SDL_DestroyWindow(window_menu_selection);
    IMG_Quit();
    SDL_Quit();
  }
