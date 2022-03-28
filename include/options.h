#ifndef OPTIONS_H_INCLUDED__
#define OPTIONS_H_INCLUDED__

#define FENETRE 0
#define BORDERLESS 1
#define FULLSCREEN 2

extern bool debug;
extern int difficulte;
extern int modeAffichage;
extern int nbreRoundsMax;

void renderMenu2();
void menu_option();


#endif