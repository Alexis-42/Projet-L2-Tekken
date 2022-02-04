#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/initSdl.h"
#include "../include/deplacements.h"

void ajouterTexte(char * txt, SDL_Color couleur, char * cheminPolice, int taillePolice, int posX, int posY, SDL_Renderer * renderer){
  SDL_Surface *texte=NULL;
  SDL_Rect txtDestRect;
  // Le pointeur vers notre police
  TTF_Init();
  TTF_Font *police = NULL;
  
  if((police = TTF_OpenFont(cheminPolice, taillePolice)) == NULL){
    fprintf(stderr , "erreur chargement font\n");
    exit(EXIT_FAILURE );
  }
  texte = TTF_RenderUTF8_Blended(police , txt, couleur);
  if(!texte){
    fprintf(stderr , "Erreur a la creation du texte : %s\n", SDL_GetError ());
    exit(EXIT_FAILURE );
  }
  SDL_SetRenderDrawColor(renderer , 0, 0, 0, 255);
  SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer , texte);
  if(! texte_tex ){
    fprintf(stderr , "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
    exit(EXIT_FAILURE );
  }
  SDL_FreeSurface(texte ); /* on a la texture , plus besoin du texte */
  /* Position ou sera mis le texte dans la fenetre */txtDestRect.x = txtDestRect.y = 10;
  SDL_QueryTexture(texte_tex , NULL , NULL , &( txtDestRect.w), &( txtDestRect.h));
}

void menu_principal(SDL_Renderer * renderer){
  // Une variable de couleur noire
  SDL_Color couleurNoire = {0, 0, 0};
  ajouterTexte("test", couleurNoire, "res/fonts/WRESTLEMANIA.ttf", 20, 10, 10, renderer);
}
