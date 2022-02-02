#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/deplacements.h"
#include "../include/main.h"

#define LARGEUR_ECRAN 1280
#define HAUTEUR_ECRAN 720

bool quit;
int x_destrec, y_destrec;

void initSdl(){ //Créé la fenêtre et l'environnement (pour l'instant)
quit = false;

SDL_Init(SDL_INIT_VIDEO);
IMG_Init(IMG_INIT_PNG);

SDL_Window * window = SDL_CreateWindow("SDL2 Tekken",
SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_ECRAN, HAUTEUR_ECRAN, 0);
SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
SDL_Surface * image_perso = IMG_Load("../res/sprites/test.png");
SDL_Surface * image_stage = IMG_Load("../res/backgrounds/stage2.png");
SDL_Texture * texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image_perso);

// SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
// SDL_RenderClear(renderer);
x_destrec = 250;
y_destrec = 575;
while (!quit){
Uint32 ticks = SDL_GetTicks();
Uint32 seconds = ticks / 250;
Uint32 sprite = seconds % 4;

SDL_Rect srcrect = { sprite * 68, 0, 68, 112 };
SDL_Rect dstrect = { x_destrec, y_destrec, 204, 336 };

actions();//Appeller la fonction dans le main pour que les actions s'actualisent

SDL_RenderClear(renderer);
SDL_RenderCopy(renderer, texture_stage, NULL, NULL);
SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
SDL_RenderPresent(renderer);
}

SDL_DestroyTexture(texture_stage);
SDL_DestroyTexture(texture);
SDL_FreeSurface(image_perso);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
IMG_Quit();
SDL_Quit();
}
