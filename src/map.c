/**
 * @file map.c
 * @author Charly.P Alexis.G Léo.N
 * @brief Fichier contenant les fonctions qui charge les map et les render
 * @version 1.0
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/map.h"
SDL_DisplayMode ecran;
SDL_Surface * image_stage = NULL;
SDL_Texture * texture_stage = NULL;

float spawnY;
int nbFramesMap, pas, h_map, h_map2, pas2;

/**
 * @brief Affiche une carte à l'écran ( sur le renderer )
 * 
 * @param src rectangle source de la texture à selectionner
 * @param dst rectangle de desination du renderer à afficher
 * @param renderer renderer sur lequel appliquer l'affichage de la carte
 */
void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer){
  SDL_RenderCopy(renderer, texture_stage, src, dst);
}

/**
 * @brief Fonction de chargement des valeurs extern et de la texure en fonction du numéro de map séléctionné
 * 
 * @param map numéro de la carte à charger
 * @param renderer renderer sur lequel afficher la carte
 * @param flag_bg flag indiquant si il s'agit de la carte du menu selection ( = carte en plut petit ) ou pas \li vaut 1 si carte \li vaut 2 si minicarte du menu selection
 * @param drip flag secret qui sert à charger la map secrète
 */
void chargerMap(int map, SDL_Renderer * renderer, int flag_bg, int drip){ // à noter revoyer un pointeur texture pour la supprimer
  char cheminMap[35];

  switch (map) {
    /*
    case -2: nbFramesMap=8;
            pas=(1886/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/flamme_sprite.png");
            break;
    */

    // bg menu selection
    case -1: nbFramesMap=16;
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/menu_selec.png");
            h_map = 336;
         pas=(12800/nbFramesMap);
            break;
    case 0: nbFramesMap=8;
            pas=(6144/nbFramesMap);
            h_map = 368;
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/menu.png");
            break;
    case 1: nbFramesMap=8;
            if(flag_bg){
                pas=(6400/nbFramesMap);
                h_map = 336;
            }else{
                pas2=(6400/nbFramesMap);
                h_map2 = 336;
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage1.png");
            spawnY=  (1097.0/1080.0)*ecran.h;
            break;
    case 2: nbFramesMap=4;
            if(flag_bg){
                h_map = 366;
                pas=(2928/nbFramesMap);
            }else{
                h_map2 = 366;
                pas2=(2928/nbFramesMap);
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage2.png");
            spawnY=(1070.0/1080.0)*ecran.h;
            break;
    case 3: nbFramesMap=14;
            if(flag_bg){
                h_map = 328;
                pas=(11200/nbFramesMap);
            }else{
                h_map2 = 328;
                pas2=(11200/nbFramesMap);
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage3.png");
            spawnY=(1070.0/1080.0)*ecran.h;
            break;
    case 4: nbFramesMap=16;
            if(flag_bg){
                pas=(12800/nbFramesMap);
                h_map = 336;
            }else{
                pas2=(12800/nbFramesMap);
                h_map2 = 336;
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage4.png");
            spawnY=(1040.0/1080.0)*ecran.h;
            break;
    case 5: nbFramesMap=7;
            if(flag_bg){
                h_map = 366;
                pas=(5124/nbFramesMap);
            }else{
                h_map2 = 366;
                pas2=(5124/nbFramesMap);
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage5.png");
            spawnY=(1040.0/1080.0)*ecran.h;
            break;
    case 6: nbFramesMap=8;
            if(flag_bg){
                h_map = 256;
                pas=(6144/nbFramesMap);
            }else{
                h_map2 = 256;
                pas2=(6144/nbFramesMap);
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage6.png");
            spawnY=(1040.0/1080.0)*ecran.h;
            break;
    case 7: nbFramesMap=7; // moche
            if(flag_bg){
                h_map = 224;
                pas=(5264/nbFramesMap);
            }else{
                h_map2 = 224;
                pas2=(5264/nbFramesMap);
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage7.png");
            spawnY=(1040.0/1080.0)*ecran.h;

            break;
    case 8: nbFramesMap=20; // à voir avec charly
            if(flag_bg){
                pas=(12800/nbFramesMap);
                h_map = 480;
            }else{
                pas2=(12800/nbFramesMap);
                h_map2 = 480;
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage8.png");
            spawnY=(1099.0/1080.0)*ecran.h;
            break;
    case 9: nbFramesMap=8;
            if(flag_bg){
                pas=(6400/nbFramesMap);
                h_map = 336;
            }else{
                pas2=(6400/nbFramesMap);
                h_map2 = 336;
            }
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage9.png");
            spawnY=(1065.0/1080.0)*ecran.h;
            break;
    case 10: nbFramesMap=8;
            if(flag_bg){
                pas=(5120/nbFramesMap);
                h_map = 384;
            }else{
                pas2=(5120/nbFramesMap);
                h_map2 = 384;
            }

            spawnY=(1060.0/1080.0)*ecran.h;
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage10.png");
            break;
    case 11:nbFramesMap=1;
            if(flag_bg){
                pas=1920;
                h_map = 1080;
            }else{
                pas2=1920;
                h_map2 = 1080;
            }

            spawnY=(1070.0/1080.0)*ecran.h;
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage11.png");
            break;
  }
  if(renderer != NULL){
        image_stage = IMG_Load(cheminMap);
        texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
        SDL_FreeSurface(image_stage);
  }
}
