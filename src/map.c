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
void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer){
  SDL_RenderCopy(renderer, texture_stage, src, dst);
}

void chargerMap(int map, SDL_Renderer * renderer, int flag_bg){ // à noter revoyer un pointeur texture pour la supprimer
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
            spawnY=  1040.0;
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
            spawnY=1040.0;
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
            spawnY=1040.0;
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
            spawnY=1040.0;
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
            spawnY=1040.0;
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
            spawnY=1040.0;
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
            spawnY=1040.0;

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
            spawnY=1040.0;
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
            spawnY=1040.0;
            break;
    case 10: nbFramesMap=8;
            if(flag_bg){
                pas=(5120/nbFramesMap);
                h_map = 384;
            }else{
                pas2=(5120/nbFramesMap);
                h_map2 = 384;
            }

            spawnY=1040.0;
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage10.png");
            break;
  }
  if(renderer != NULL){
        image_stage = IMG_Load(cheminMap);
        texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
        SDL_FreeSurface(image_stage);
  }
}
