/* complex.h */
#ifndef COMPLEX_H_INCLUDED__
#define COMPLEX_H_INCLUDED__
#include <SDL2/SDL.h>
#include <stdbool.h>

// normalement 220 et 76
#define TAILLE_X_JOUEUR 176
#define TAILLE_Y_JOUEUR 320

typedef enum {gauche, droite} Direction;

typedef struct {
	int x, y;
} coord;

typedef struct {
  coord position;
  int vie;
  int action;
  Direction direction;
	Personnage perso;
  char * nom;
  SDL_Rect hitbox;
  SDL_Rect srcrect;
  SDL_Rect dstrect;
} Joueur;

void direction(Joueur * j1, Joueur * j2);
void hitbox(Joueur * joueur);
void checkPerdu(Joueur * j1, Joueur * j2);
bool checkCollisions(Joueur * j1, Joueur * j2);
void initJoueur(Joueur * joueur, float posX, char * pseudo, SDL_Texture * texture, Direction direction);
#endif
