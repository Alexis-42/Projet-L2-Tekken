/**
 * @file main.c
 * @author Notelet Léo, Pecquery Charly, Guimbert Alexis
 * @brief fichier qui vérifie les arguments données en entré
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/initSdl.h"
#include "../include/menu_principal.h"
#include "../include/jeu.h"

/**
 * @brief fonction qui vérifie les argument d'entré de la fonction et qui active certaine fonctionnalité en fonction de l'argument
 * 
 * @param argc nombre d'élément de la ligne de commande
 * @param argv contient les éléments de la ligne de commande dans un tableau de chaine de caractères
 * @return int 
 */
int main(int argc, char *argv[]) {
  // 1 si drip
  if(argc>=2){
    if(strcmp(argv[1],"drip")==0)
      menu_principal(1);
  } else
    menu_principal(0);
  return 0;
}
