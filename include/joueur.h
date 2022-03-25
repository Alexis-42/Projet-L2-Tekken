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
	SDL_Rect hitbox; //Hitbox pour recevoir des degats et le reste
	SDL_Rect hitbox_coup; //Hitbox pour la portée des coups de poing
  SDL_Rect hitbox_pied; //Hitbox pour la portée des coups de pieds
	SDL_Texture * texture;
  char * nom;
} Joueur;

bool estTropHaut(Joueur * joueur);
bool estAuSol(Joueur * joueur);
void direction(Joueur * j1, Joueur * j2);
void hitbox(Joueur * joueur, SDL_Texture * texture,int coup);
void checkPerdu(Joueur * j1, Joueur * j2);
bool checkCollisions(Joueur * j1, Joueur * j2);
void initJoueur(Joueur * joueur, float posX, char * pseudo, SDL_Texture * texture, Direction direction);
void initPerso(Joueur * j, int i);
#endif
