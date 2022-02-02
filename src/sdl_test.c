#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>


int main(int argc, char ** argv)
{
bool quit = false;
SDL_Event event;

SDL_Init(SDL_INIT_VIDEO);
IMG_Init(IMG_INIT_PNG);

SDL_Window * window = SDL_CreateWindow("SDL2 Sprite Sheets",
SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);
SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
SDL_Surface * image_perso = IMG_Load("test.png");
SDL_Surface * image_stage = IMG_Load("stage2.png");
SDL_Texture * texture_stage = SDL_CreateTextureFromSurface(renderer, image_stage);
SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image_perso);

// SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
// SDL_RenderClear(renderer);
int x_destrec = 250;
int y_destrec = 575;
while (!quit)
{
Uint32 ticks = SDL_GetTicks();
Uint32 seconds = ticks / 250;
Uint32 sprite = seconds % 4;

SDL_Rect srcrect = { sprite * 68, 0, 68, 112 };
SDL_Rect dstrect = { x_destrec, y_destrec, 204, 336 };


// SDL_WaitEvent(&event);
SDL_PollEvent(&event);
switch (event.type)
{
case SDL_QUIT:
quit = true;
break;
case SDL_KEYDOWN:
switch(event.key.keysym.sym)
{
case SDLK_q:
x_destrec-=10;
break;
case SDLK_d:
x_destrec+=10;
break;
}

}

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

return 0;
}
