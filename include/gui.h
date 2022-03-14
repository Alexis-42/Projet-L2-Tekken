#include "../include/joueur.h"
#ifndef ANIM_H_INCLUDED__
#define ANIM_H_INCLUDED__

void init_affichage_temps(int sec_deb_combat,TTF_Font* font, SDL_Rect * rect_sprite_pvj1);
void init_sprite_pv(SDL_Rect * rect_sprite_pv,int num_joueur);
void afficher_nom_joueur(Joueur * joueur, TTF_Font* font, SDL_Rect * rect_sprite_pv);
void barre_de_vie(Joueur * joueur, SDL_Rect * rect_sprite_pv, SDL_Texture * texture_barre_de_vie, SDL_Texture * texture_carre_rouge, SDL_Texture * texture_carre_jaune, int num_joueur, TTF_Font* font);
void init_gui(SDL_Texture ** texture_carre_jaune, SDL_Texture ** texture_carre_rouge, SDL_Surface * sprite_barre_de_vie, SDL_Texture ** texture_barre_de_vie);

#endif
