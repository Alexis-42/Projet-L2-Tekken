/* complex.h */
#ifndef COMPLEX_H_INCLUDED__
#define COMPLEX_H_INCLUDED__
#include <SDL2/SDL.h>
#include <stdbool.h>

#define TAILLE_X_JOUEUR 380
#define TAILLE_Y_JOUEUR 640

typedef enum {gauche, droite} Direction;

typedef struct {
	int x, y;
} coord;

typedef struct {
  coord position;
  int vie;
  int action;
  Direction direction;
  char * nom;
  SDL_Texture * texture;
  SDL_Rect hitbox;
  SDL_Rect srcrect;
  SDL_Rect dstrect;
} Joueur;

/* struc qui permet de faire le menu de selection des persos */
struct personnage {
    char * nom;
    char * sprite;
    int taille_y;
    int taille_x;
};

void direction(Joueur * j1, Joueur * j2);
void hitbox(Joueur * joueur);
void checkPerdu(Joueur * j1, Joueur * j2);
bool checkCollisions(Joueur * j1, Joueur * j2);
void initJoueur(Joueur * joueur, float posX, char * pseudo, SDL_Texture * texture, Direction direction);
#endif
