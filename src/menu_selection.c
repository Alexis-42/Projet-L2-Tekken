#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/menu_principal.h"
#include "../include/jeu.h"




void aff_menu_selection(int carre,float pos_x){}












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
    SDL_FreeSurface(image_shrek);
    SDL_Rect rect_shrek;
    rect_shrek.x = 200.0/1920.0*ecran.w;
    rect_shrek.y = 700.0/1080.0*ecran.h;
    rect_shrek.w = ecran.w/6.0;
    rect_shrek.h = ecran.w/6.0;

   //image de goku
    SDL_Surface * image_goku = IMG_Load("res/goku.png");
    SDL_Texture * texture_goku = SDL_CreateTextureFromSurface(renderer_menu_selection, image_goku);
    SDL_FreeSurface(image_goku);
    SDL_Rect rect_goku;
    rect_goku.x = 600.0/1920.0*ecran.w;
    rect_goku.y = 700.0/1080.0*ecran.h;
    rect_goku.w = ecran.w/6.0;
    rect_goku.h = ecran.w/6.0;

   //image de pingu
    SDL_Surface * image_pingu = IMG_Load("res/pingu.png");
    SDL_Texture * texture_pingu = SDL_CreateTextureFromSurface(renderer_menu_selection, image_pingu);
    SDL_FreeSurface(image_pingu);
    SDL_Rect rect_pingu;
    rect_pingu.x = 1000.0/1920.0*ecran.w;
    rect_pingu.y = 700.0/1080.0*ecran.h;
    rect_pingu.w = ecran.w/6.0;
    rect_pingu.h = ecran.w/6.0;

   //image de tinky
    SDL_Surface * image_tinky = IMG_Load("res/tinky.png");
    SDL_Texture * texture_tinky = SDL_CreateTextureFromSurface(renderer_menu_selection, image_tinky);
    SDL_FreeSurface(image_tinky);
    SDL_Rect rect_tinky;
    rect_tinky.x = 1400.0/1920.0*ecran.w;
    rect_tinky.y = 700.0/1080.0*ecran.h;
    rect_tinky.w = ecran.w/6.0;
    rect_tinky.h = ecran.w/6.0;

//carrés qui s'affichent derriere le personnage que les joueurs sélectionnent
    //carré rouge de sélection du personnage 
    SDL_Surface * image_carre_rouge = IMG_Load("res/carre_rouge.png");
    SDL_Texture * texture_carre_rouge = SDL_CreateTextureFromSurface(renderer_menu_selection, image_carre_rouge);
    SDL_FreeSurface(image_carre_rouge);
    SDL_Rect rect_carre_rouge;
    rect_carre_rouge.x = ecran.w+10000;
    rect_carre_rouge.y = 700.0/1080.0*ecran.h;
    rect_carre_rouge.w = ecran.w/6.0;
    rect_carre_rouge.h = ecran.w/6.0;

    //carré bleu de sélection du personnage 
    SDL_Surface * image_carre_bleu = IMG_Load("res/carre_bleu.png");
    SDL_Texture * texture_carre_bleu = SDL_CreateTextureFromSurface(renderer_menu_selection, image_carre_bleu);
    SDL_FreeSurface(image_carre_bleu);
    SDL_Rect rect_carre_bleu;
    rect_carre_bleu.x = 600.0/1920.0*ecran.w;
    rect_carre_bleu.y = 700.0/1080.0*ecran.h;
    rect_carre_bleu.w = ecran.w/6.0;
    rect_carre_bleu.h = ecran.w/6.0;

    //carré violet de sélection du personnage si les 2 joueurs choissisent le meme
    SDL_Surface * image_carre_violet = IMG_Load("res/carre_violet.png");
    SDL_Texture * texture_carre_violet = SDL_CreateTextureFromSurface(renderer_menu_selection, image_carre_violet);
    SDL_FreeSurface(image_carre_violet);
    SDL_Rect rect_carre_violet;
    rect_carre_violet.x = ecran.w+10000;
    rect_carre_violet.y = 700.0/1080.0*ecran.h;
    rect_carre_violet.w = ecran.w/6.0;
    rect_carre_violet.h = ecran.w/6.0;






//affichage de la page
    SDL_RenderClear(renderer_menu_selection);
    SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
    //SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
    //SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
    SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
    SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
    SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
    SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
    SDL_RenderPresent(renderer_menu_selection);

//recherche des actions

    int x_button;
  	int y_button;
    int tour_joueur;

    bool quitter=false;
    while (!quitter) {
        SDL_Event event;
  	    SDL_WaitEvent(&event);
    	switch (event.type){
  	    	case SDL_QUIT:
  	    		quitter = true;
  	    		break;
            case SDL_MOUSEBUTTONDOWN:
  				x_button =event.button.x;
  				y_button =event.button.y;
  				printf("\n%i %i",x_button,y_button);
                  //carre 1er pers
                    if(x_button>(200.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(200.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
                        if(tour_joueur){
                            rect_carre_bleu.x = 200.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=0;
                        }else{
                            rect_carre_rouge.x = 200.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=1;
                        }
                        //carre 2eme pers
                    }else if(x_button>(600.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(600.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
                        if(tour_joueur){
                            rect_carre_bleu.x = 600.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=0;
                        }else{
                            rect_carre_rouge.x = 600.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=1;
                        }
                        //carre 3eme pers
                    }else if(x_button>(1000.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(1000.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
                        if(tour_joueur){
                            rect_carre_bleu.x = 1000.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=0;
                        }else{
                            rect_carre_rouge.x = 1000.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=1;
                        }
                        //carre 4eme pers
                    }else if(x_button>(1400.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(1400.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
                        if(tour_joueur){
                            rect_carre_bleu.x = 1400.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=0;
                        }else{
                            rect_carre_rouge.x = 1400.0/1920.0*ecran.w;
                            SDL_RenderClear(renderer_menu_selection);
                            SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
                            SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
                            if(rect_carre_bleu.x == rect_carre_rouge.x){
                                SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
                            }
                            SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
                            SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
                            SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
                            SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
                            SDL_RenderPresent(renderer_menu_selection);
                            tour_joueur=1;
                        }
                    }
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
