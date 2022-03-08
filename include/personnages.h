#ifndef PERSO_H_INCLUDED__
#define PERSO_H_INCLUDED__

/* struc qui permet de faire le menu de selection des persos */
typedef struct {
    char * nom;
    char * sprite;
    SDL_Texture * texture;
    int taille_y;
    int taille_x;
} Personnage;

#endif
