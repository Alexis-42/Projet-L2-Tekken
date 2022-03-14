#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/map.h"
SDL_DisplayMode ecran;
SDL_Surface * image_stage = NULL;
SDL_Texture * texture_stage = NULL;

float spawnY;
int nbFramesMap, pas;
char * cheminMap;

void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer){
  SDL_RenderCopy(renderer, texture_stage, src, dst);
}

void chargerMap(int map, SDL_Renderer * renderer){
  cheminMap = malloc(sizeof(char *));

  switch (map) {
    case 0: nbFramesMap=8;
            pas=(6144/nbFramesMap);
            cheminMap="res/backgrounds/menu.png";
            break;
    case 1: nbFramesMap=7;
            pas=(5124/nbFramesMap);
            cheminMap="res/backgrounds/stage1.png";
            spawnY=(450.0/1080.0)*ecran.h;
            break;
    case 2: nbFramesMap=4;
            pas=(2928/nbFramesMap);
            cheminMap="res/backgrounds/stage2.png";
            spawnY=(450.0/1080.0)*ecran.h;
            break;
    case 3: nbFramesMap=14;
            pas=(11200/nbFramesMap);
            cheminMap="res/backgrounds/stage3.png";
            spawnY=(500.0/1080.0)*ecran.h;
            break;
  }

  image_stage = IMG_Load(cheminMap);
  texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
}
