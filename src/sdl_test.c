#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
int main(int argc , char ** argv)
{
//Le pointeur vers la fenetreSDL_Window* pWindow = NULL;
//Le pointeur vers la surface incluse dans la fenetre
SDL_Surface *texte=NULL , *image=NULL;SDL_Renderer *renderer=NULL;SDL_Rect txtDestRect ,imgDestRect;
// Le pointeur vers notre policeTTF_Font *police = NULL;
// Une variable de couleur noire
SDL_Color couleurNoire = {0, 0, 0};
/* Initialisation simple */
if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
fprintf(stdout ,"Echec de l’initialisation de la SDL (%s)\n",SDL_GetError ());return -1;
}
/* Initialisation TTF */
if(TTF_Init () == -1) {
fprintf(stderr , "Erreur d’initialisation de TTF_Init : %s\n", TTF_GetError ());
exit(EXIT_FAILURE );
}
/* Creation de la fenetre */
pWindow = SDL_CreateWindow ("Hello World SDL2",SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED ,640,480,
SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE );
if(! pWindow ){
fprintf(stderr , "Erreur a la creation de la fenetre : %s\n", SDL_GetError ());
exit(EXIT_FAILURE );
}
renderer = SDL_CreateRenderer(pWindow , -1, SDL_RENDERER_ACCELERATED );
if(renderer == NULL){
fprintf(stderr , "Erreur a la creation du renderer\n");
exit(EXIT_FAILURE );
}
if( (police = TTF_OpenFont("ChowFun.ttf", 20)) == NULL){
fprintf(stderr , "erreur chargement font\n");
exit(EXIT_FAILURE );
}
texte = TTF_RenderUTF8_Blended(police , "Vive la programmation !", couleurNoire );
if(!texte){
fprintf(stderr , "Erreur a la creation du texte : %s\n", SDL_GetError ());
exit(EXIT_FAILURE );
}
SDL_SetRenderDrawColor(renderer , 0, 0, 0, 255);
SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer , texte);
if(! texte_tex ){
fprintf(stderr , "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
exit(EXIT_FAILURE );
}
SDL_FreeSurface(texte ); /* on a la texture , plus besoin du texte */
/* Position ou sera mis le texte dans la fenetre */txtDestRect.x = txtDestRect.y = 10;
SDL_QueryTexture(texte_tex , NULL , NULL , &( txtDestRect.w), &( txtDestRect.h));
// load sample.png into image
SDL_RWops *rwop=SDL_RWFromFile("affiche2018.png", "rb");
image=IMG_LoadPNG_RW(rwop);
if(!image) {
printf("IMG_LoadPNG_RW: %s\n", IMG_GetError ());
}

SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer , image);
if(! image_tex ){
fprintf(stderr , "Erreur a la creation du rendu de l’image : %s\n", SDL_GetError ());
exit(EXIT_FAILURE );
}
SDL_FreeSurface(image ); /* on a la texture , plus besoin de l’image */
if( pWindow )
{ int running = 1;
while(running) {SDL_Event e;
while(SDL_PollEvent (&e)) {
switch(e.type) {case SDL_QUIT: running = 0;
break;case SDL_WINDOWEVENT:
switch(e.window.event){case SDL_WINDOWEVENT_EXPOSED:case SDL_WINDOWEVENT_SIZE_CHANGED:case SDL_WINDOWEVENT_RESIZED:case SDL_WINDOWEVENT_SHOWN:
/* Le fond de la fenetre sera blanc */
SDL_SetRenderDrawColor(renderer , 255, 255, 255, 255);
SDL_RenderClear(renderer );
/* Ajout du texte en noir */
SDL_SetRenderDrawColor(renderer , 0, 0, 0, 255);
SDL_RenderCopy(renderer , texte_tex , NULL , &txtDestRect );
/* Ajout de la seconde image a une certaine position */imgDestRect.x = imgDestRect.y = 50;
SDL_QueryTexture(image_tex , NULL , NULL , &( imgDestRect.w),
&( imgDestRect.h));
SDL_RenderCopy(renderer , image_tex , NULL , &imgDestRect );
/* Ajout de la seconde image a une autre position */imgDestRect.x = 250;
SDL_RenderCopy(renderer , image_tex , NULL , &imgDestRect );
/* On fait le rendu ! */
SDL_RenderPresent(renderer );
break;
}
break;
}
}
}
} else {
fprintf(stderr ,"Erreur de creation de la fenetre: %s\n",SDL_GetError ());
}
// Destruction de la fenetre
SDL_DestroyWindow (pWindow );
TTF_CloseFont(police ); /* Doit etre avant TTF_Quit () */
TTF_Quit ();
SDL_Quit ();
return 0;
}
