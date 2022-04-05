/**
 * @file options.h
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier header des fonctions qui permettent l'affichage de la pause & sauvegarde / chargement des options
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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