/* complex.h */
#ifndef COMPLEX_H_INCLUDED__
#define COMPLEX_H_INCLUDED__
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/personnages.h"

typedef enum {gauche, droite} Direction;

typedef struct {
	float x, y;
} coord;

typedef struct {
  coord position;
  int vie;
  int action;
  Direction direction;
	Personnage perso;
	SDL_Rect hitbox;
	SDL_Texture * texture;
  char * nom;
} Joueur;

void initPerso(Joueur * j, int i);

void direction(Joueur * j1, Joueur * j2);
void hitbox(Joueur * joueur);
void checkPerdu(Joueur * j1, Joueur * j2);
bool checkCollisions(Joueur * j1, Joueur * j2);
void initJoueur(Joueur * joueur, float posX, char * pseudo, SDL_Texture * texture, Direction direction);
#endif
