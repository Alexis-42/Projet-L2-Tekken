#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/map.h"
SDL_DisplayMode ecran;
SDL_Surface * image_stage = NULL;
SDL_Texture * texture_stage = NULL;

float spawnY;
int nbFramesMap, pas, h_map;
void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer){
  SDL_RenderCopy(renderer, texture_stage, src, dst);
}

void chargerMap(int map, SDL_Renderer * renderer){ // à noter revoyer un pointeur texture pour la supprimer
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
            pas=(12800/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/menu_selec.png");
            h_map = 336;
            break;
    case 0: nbFramesMap=8;
            pas=(6144/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/menu.png");
            h_map = 368;
            break;
    case 1: nbFramesMap=8;
            pas=(6400/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage1.png");
            spawnY=(500.0/1080.0)*ecran.h;
            h_map = 336;
            break;
    case 2: nbFramesMap=4;
            pas=(2928/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage2.png");
            spawnY=(450.0/1080.0)*ecran.h;
            h_map = 366;
            break;
    case 3: nbFramesMap=14;
            pas=(26112/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage3.png");
            spawnY=(500.0/1080.0)*ecran.h;
            h_map = 328;
            break;
    case 4: nbFramesMap=16;
            pas=(12800/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage4.png");
            spawnY=(500.0/1080.0)*ecran.h;
            h_map = 336;
            break;
    case 5: nbFramesMap=7;
            pas=(5124/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage5.png");
            spawnY=(450.0/1080.0)*ecran.h;
            h_map = 366;
            break;
    case 6: nbFramesMap=8;
            pas=(6144/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage6.png");
            spawnY=(500.0/1080.0)*ecran.h;
            h_map = 256;
            break;
    case 7: nbFramesMap=7; // moche
            pas=(5264/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage7.png");
            spawnY=(450.0/1080.0)*ecran.h;
            h_map = 224;
            break;
    case 8: nbFramesMap=20; // à voir avec charly
            pas=(12800/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage8.png");
            spawnY=(500.0/1080.0)*ecran.h;
            h_map = 480;
            break;
    case 9: nbFramesMap=8;
            pas=(6400/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage9.png");
            spawnY=(475.0/1080.0)*ecran.h;
            h_map = 336;
            break;
    case 10: nbFramesMap=8;
            pas=(5120/nbFramesMap);
            snprintf(cheminMap, sizeof(cheminMap), "res/backgrounds/stage10.png");
            spawnY=(475.0/1080.0)*ecran.h;
            h_map = 384;
            break;
  }
  image_stage = IMG_Load(cheminMap);
  texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
  SDL_FreeSurface(image_stage);
}
