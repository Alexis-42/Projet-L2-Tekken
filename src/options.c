#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/jeu.h"
#include "../include/menu_selection.h"
#include "../include/animations.h"
#include "../include/map.h"
#include "../include/menu.h"
#include "../include/options.h"

bool quitter;
char pref_path[100];

SDL_Surface * image_stage_menu;
SDL_Surface * surface_jonathan;
SDL_Rect srcBg, dstBg;
SDL_DisplayMode ecran;
SDL_Rect btn1, btn2, btn3, btn4, btn5;
SDL_Texture * texBtn1, * texBtn2, * texBtn3, * texBtn4, * texBtn5, * texture_jonathan;

SDL_Rect flamme1, flamme2, flamme3, flamme4, flamme5;
SDL_Texture * texFlamme1, * texFlamme2, * texFlamme3, * texFlamme4, * texFlamme5;

void sauvPreferences(FILE * fichier){
  fprintf(fichier, "difficulte:%d\n", difficulte);
  fprintf(fichier, "debug:%d\n", debug);
  fprintf(fichier, "mode:%d\n", modeAffichage);
  fprintf(fichier, "nbrounds:%d\n", nbreRoundsMax);
}

void chargerPreferences(FILE * fichier){
  char * nothing = NULL;
  fscanf(fichier, "%s:%d", nothing, &difficulte);
  fscanf(fichier, "%s:%d", nothing, &debug);
  fscanf(fichier, "%s:%d", nothing, &modeAffichage);
  fscanf(fichier, "%s:%d", nothing, &nbreRoundsMax);
}

int getSelection3(int x_button, int y_button){
  if(x_button>btn1.x && y_button>btn1.y && x_button<btn1.x+600.0 && y_button<btn1.y+100.0)
    return 1;
  else if(x_button>btn2.x && y_button>btn2.y && x_button<btn2.x+600.0 && y_button<btn2.y+100.0)
    return 2;
  else if(x_button>btn3.x && y_button>btn3.y && x_button<btn3.x+600.0 && y_button<btn3.y+100.0)
    return 3;
  else if(x_button>btn4.x && y_button>btn4.y && x_button<btn4.x+600.0 && y_button<btn4.y+100.0)
    return 4;
  else if(x_button>btn5.x && y_button>btn5.y && x_button<btn5.x+600.0 && y_button<btn5.y+100.0)
    return 5;
  return 0;
}

  void renderMenu2(int sortie, int drip){
    SDL_RenderClear(renderer);
    
    jouerAnimationBackground(&srcBg, &dstBg,1);
    renderMap(&srcBg, &dstBg, renderer);

    switch (sortie) {
      case 1: SDL_RenderCopy(renderer, texFlamme1, NULL, &flamme1); break;
      case 2: SDL_RenderCopy(renderer, texFlamme2, NULL, &flamme2); break;
      case 3: SDL_RenderCopy(renderer, texFlamme3, NULL, &flamme3); break;
      case 4: SDL_RenderCopy(renderer, texFlamme4, NULL, &flamme4); break;
      case 5: SDL_RenderCopy(renderer, texFlamme5, NULL, &flamme5); break;
    }

    SDL_RenderCopy(renderer, texBtn1, NULL, &btn1);
    SDL_RenderCopy(renderer, texBtn2, NULL, &btn2);
    SDL_RenderCopy(renderer, texBtn3, NULL, &btn3);
    SDL_RenderCopy(renderer, texBtn4, NULL, &btn4);
    SDL_RenderCopy(renderer, texBtn5, NULL, &btn5);
    SDL_RenderPresent(renderer);
  }
  
  FILE * chargerFichierPref(char * nomFichier){
    char *base_path = SDL_GetPrefPath("ProjetL2", "Tekken");
    if (base_path) {
        snprintf(pref_path, sizeof(pref_path), "%s%s", base_path, nomFichier);
    }

    FILE * fichier_prefs = NULL;
    //if(debug)
      printf("%s\n", pref_path);

    if(!(fichier_prefs = fopen(pref_path, "r"))){
      fichier_prefs = fopen(pref_path, "w");
      sauvPreferences(fichier_prefs);
      printf("Fichier créé !");
    }
    return fichier_prefs;
  }

  void menu_option(int drip){
    char difficulteTexte[50], debugTexte[50], modeTexte[50], roundsTexte[50];
    char * listeDifficultes[] = {"Punching Ball", "Facile", "Normal", "Difficile", "Cauchemard", "Dieu"};
    char * listeDebug[] = {"Desactive", "Active"};
    char * listeModes[] = {"Fenetre", "Sans bordure", "Plein ecran"};

    if(TTF_Init()==-1){
      printf("librairie non initialisé");
      exit(EXIT_FAILURE);
    }
    
    chargerMap(0, renderer,1,drip);
  //preparation arriere plan texte
    //fond texte flamme multijoueur
    initFlammes(&flamme1, &texFlamme1, 75.0, 25.0);
    initFlammes(&flamme2, &texFlamme2, 75.0, 125.0);
    initFlammes(&flamme3, &texFlamme3, 75.0, 225.0);
    initFlammes(&flamme4, &texFlamme4, 75.0, 325.0);
    initFlammes(&flamme5, &texFlamme5, 75.0, 425.0);

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

    snprintf(difficulteTexte, sizeof(difficulteTexte), "Difficulte : %s", listeDifficultes[difficulte]);
    snprintf(debugTexte, sizeof(debugTexte), "Debug : %s", listeDebug[debug]);
    snprintf(modeTexte, sizeof(modeTexte), "Mode : %s", listeModes[modeAffichage]);
    snprintf(roundsTexte, sizeof(roundsTexte), "Nombre de rounds : %d", nbreRoundsMax);

    //création affichage jouer en multijoueur
    creerBouton(font, difficulteTexte, ColorWhite, &btn1, &texBtn1, 75.0, 50.0);
    creerBouton(font, debugTexte, ColorWhite, &btn2, &texBtn2, 75.0, 150.0);
    creerBouton(font, modeTexte, ColorWhite, &btn3, &texBtn3, 75.0, 250.0);
    creerBouton(font, roundsTexte, ColorWhite, &btn4, &texBtn4, 75.0, 350.0);
    creerBouton(font, "Sauvegarder et quitter", ColorWhite, &btn5, &texBtn5, 75.0, 450.0);

   
    //affichage du fond d'écran apres avoir néttoyer le renderer
   	int x_button;
  	int y_button;
    quitter=false;
    int sortie=1;

  while (!quitter) {
  	SDL_Event event;
  	//SDL_WaitEvent(&event);
  	SDL_PollEvent(&event);
    renderMenu2(sortie, drip);

  	switch (event.type){
  		case SDL_QUIT:
  			quitter = true;
  			break;
  		case SDL_MOUSEBUTTONDOWN:
  				x_button =event.button.x;
  				y_button =event.button.y;
          //sortie jouer en multijoueur

          switch (getSelection3(x_button, y_button)) {
            case 1: if(difficulte<5)
                        difficulte++;
                    else
                        difficulte=0;
                    sortie=1;
                    snprintf(difficulteTexte, sizeof(difficulteTexte), "Difficulte : %s", listeDifficultes[difficulte]);
                    creerBouton(font, difficulteTexte, ColorWhite, &btn1, &texBtn1, 75.0, 50.0);
                    break;
            case 2: debug=!debug;
                    sortie=2;
                    snprintf(debugTexte, sizeof(debugTexte), "Debug : %s", listeDebug[debug]);
                    creerBouton(font, debugTexte, ColorWhite, &btn2, &texBtn2, 75.0, 150.0);
                    break;
            case 3: if(modeAffichage<2)
                        modeAffichage++;
                    else
                        modeAffichage=0;
                    sortie=3;
                    snprintf(modeTexte, sizeof(modeTexte), "Mode : %s", listeModes[modeAffichage]);
                    creerBouton(font, modeTexte, ColorWhite, &btn3, &texBtn3, 75.0, 250.0);
                    break;
            case 4: if(nbreRoundsMax<10)
                        nbreRoundsMax++;
                    else
                        nbreRoundsMax=1;
                    sortie=4;
                    snprintf(roundsTexte, sizeof(roundsTexte), "Nombre de rounds : %d", nbreRoundsMax);
                    creerBouton(font, roundsTexte, ColorWhite, &btn4, &texBtn4, 75.0, 350.0);
                    break;
            case 5: 
                    freopen(pref_path, "w", fichier_prefs);
                    sauvPreferences(fichier_prefs);
                    quitter=true;
                    sortie=5;
                    break;
          }
  				break;

      case SDL_MOUSEMOTION:
        	x_button =event.button.x;
  				y_button =event.button.y;
      //postions de la souris
          //sur le texte multijoueur

          switch (getSelection3(x_button, y_button)) {
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
            case 5:
                    sortie=5;
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
          }else if(sortie==5){
              sortie=4;
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
          }else if(sortie==4){
              sortie=5;
        }
  		}
  	}
  }
    //fin du menu principal, changement de fenetre
    fclose(fichier_prefs);
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(texFlamme1);
    SDL_DestroyTexture(texFlamme2);
    SDL_DestroyTexture(texFlamme3);
    SDL_DestroyTexture(texFlamme4);
    SDL_DestroyTexture(texBtn1);
    SDL_DestroyTexture(texBtn2);
    SDL_DestroyTexture(texBtn3);
    SDL_DestroyTexture(texBtn4);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    lancerMenu(MENU_PRINCIPAL, 0, 0);
    IMG_Quit();
    SDL_Quit();
    //redirection vers la sortie souhaité
  }
