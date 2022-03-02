#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/joueur.h"
#include "../include/jeu.h"
#include "../include/animations.h"

void initJoueur(Joueur * joueur, int posX, SDL_Texture * texture){
  joueur->vie=100;
  joueur->action=IDLE;
  joueur->nom="test";
  joueur->texture=texture;
  joueur->posX=posX;
  joueur->posY=(float) 425/900*ecran.h; //425 est la valeur qui convient quand la résolution est de 900px, il faut rester proportionel avec la taille de l'écran utilisé, possiblement foireux
}
