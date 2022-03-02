/* complex.h */
#ifndef COMPLEX_H_INCLUDED__
#define COMPLEX_H_INCLUDED__
#include <SDL2/SDL.h>

typedef enum {droite, gauche} Direction;

typedef struct {
  int posX, posY;
  int vie;
  int action;
  Direction direction;
  char * nom;
  SDL_Texture * texture;
  SDL_Rect srcrect;
  SDL_Rect dstrect;
} Joueur;

/* struc qui permet de fair le menu de selection des persos */
struct personnage {
    char * nom;
    char * sprite;
    int taille_y;
    int taille_x;
};

void initJoueur(Joueur * joueur, int posX, SDL_Texture * texture, Direction direction);
#endif
