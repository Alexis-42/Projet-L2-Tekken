#include "../include/joueur.h"

#define COURIR 0
#define POING 1
#define PARER 2

void jouerAnimation(int anim, Joueur * joueur);
void renderAnimation(SDL_Renderer * renderer, SDL_Texture * texture, Joueur * joueur);
