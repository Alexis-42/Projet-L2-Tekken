#ifndef OPTIONS_H_INCLUDED__
#define OPTIONS_H_INCLUDED__

#define FENETRE 0
#define BORDERLESS 1
#define FULLSCREEN 2

extern int debug;
extern int difficulte;
extern int modeAffichage;
extern int nbreRoundsMax;

void renderMenu2();
void menu_option();
void sauvPreferences(FILE * fichier);
void chargerPreferences(FILE * fichier);
FILE * chargerFichierPref(char * nomFichier);

#endif