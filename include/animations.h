#include "../include/joueur.h"
#ifndef ANIM_H_INCLUDED__
#define ANIM_H_INCLUDED__

#define DANSE 0
#define DEGAT 1
#define IDLE 2
#define MORT 3
#define PIED 4
#define POING 5
#define COURIR 6
#define SAUTER 7
#define PARER 8

void renderAnimation(Joueur * joueur);
void jouerAnimation(Joueur * joueur,int seconds,Joueur * j2);
void jouerAnimationContinu(Joueur * joueur,int seconds);
void jouerAnimationBackground(SDL_Rect * srcBg, SDL_Rect * dstBg,int flag_bg);

typedef struct {
  int posY;
  int nb_frames;
  char * chemin_sprite;
} Background;

#endif
