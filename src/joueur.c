#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "../include/joueur.h"

void initJoueur(Joueur * joueur){
  joueur->vie=100;
  joueur->nom="test";
}
