#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/menu_principal.h"
#include "../include/jeu.h"
#include "../include/joueur.h"
#include "../include/personnages.h"
#include "../include/animations.h"

#define MODE FULLSCREEN
SDL_Window * window_menu_selection=NULL;

void aff_menu_selection(int carre,float pos_x){}

SDL_Texture * creat_texture_rect(char * chemin_img, SDL_Rect * rect, SDL_Renderer * renderer, int x, int y, int w, int h){
  /* creation de la texture */
  SDL_Surface * img = IMG_Load(chemin_img);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);
  /* init des valeurs du rect correspondant */
  if(rect != NULL){
    rect->x= x;
    rect->y= y;
    rect->w= w;
    rect->h= h;
  }
  return texture;
}

void jouerAnimationPersoMenu(Joueur * joueur, int tour, double cord_perso){ //Pour freezer l'anim il faut anuller le getTick
Uint32 seconds = SDL_GetTicks() / 100; //Fréquence (toutes les 30ms)
Uint32 sprite = seconds % 15;
float posx;
if(tour){
  posx=100.0;
}else{
  posx=1500.0;
}
SDL_Rect srcrect;
SDL_Rect dstrect;

//shrek
//  if(cord_perso==200.0/1920.0*ecran.w){
srcrect.x = sprite * 540;
srcrect.y = 0;
srcrect.w = joueur->perso.taille_perso.w;
srcrect.h = joueur->perso.taille_perso.h;

dstrect.x = posx/1920*ecran.w;
dstrect.y = 300/1080.0*ecran.h;
dstrect.w = joueur->perso.taille_perso.w;
dstrect.h = joueur->perso.taille_perso.h;

joueur->perso.srcrect=srcrect;
joueur->perso.dstrect=dstrect;
//}
}

void menu_selection(){

  //initialisation de sdl
  if(TTF_Init()==-1){
    printf("librairie non initialisé");
    exit(EXIT_FAILURE);
  }
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  //création de la page
  switch(MODE){
    case FULLSCREEN:
    window_menu_selection = SDL_CreateWindow("SDL2 Tekken - menu selection personnage",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_FULLSCREEN);
    break;
    case BORDERLESS:
    window_menu_selection = SDL_CreateWindow("SDL2 Tekken - menu selection personnage",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ecran.w, ecran.h, SDL_WINDOW_BORDERLESS);
    break;
  }

  SDL_Renderer * renderer_menu_selection = SDL_CreateRenderer(window_menu_selection, -1, 0);
  SDL_Surface * image_stage_menu_selection = IMG_Load("res/backgrounds/selectperso.png");
  SDL_Texture * texture_stage_menu_selection = SDL_CreateTextureFromSurface(renderer_menu_selection, image_stage_menu_selection);
  SDL_FreeSurface(image_stage_menu_selection);

  //preparation image des personnages
  //image de shrek
  SDL_Rect rect_shrek;
  SDL_Texture * texture_shrek = creat_texture_rect("res/shrek.png", &rect_shrek, renderer_menu_selection, 200.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);  
  SDL_Rect rect_bg_shrek;
  SDL_Texture * texture_bg_shrek = creat_texture_rect("res/carre_gris.png", &rect_bg_shrek, renderer_menu_selection, 200.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_contour_shrek;
  SDL_Texture * texture_contour_shrek = creat_texture_rect("res/carre_perso.png", &rect_contour_shrek, renderer_menu_selection, (200.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);  

  //image de goku
  SDL_Rect rect_goku;
  SDL_Texture * texture_goku = creat_texture_rect("res/goku.png", &rect_goku, renderer_menu_selection, 600.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_goku;
  SDL_Texture * texture_bg_goku = creat_texture_rect("res/carre_gris.png", &rect_bg_goku, renderer_menu_selection, 600.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);

  SDL_Rect rect_contour_goku;
  SDL_Texture * texture_contour_goku = creat_texture_rect("res/carre_perso.png", &rect_contour_goku, renderer_menu_selection, (600.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);  

  //image de pingu
  SDL_Rect rect_pingu;
  SDL_Texture * texture_pingu = creat_texture_rect("res/pingu.png", &rect_pingu, renderer_menu_selection, 1000.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_pingu;
  SDL_Texture * texture_bg_pingu = creat_texture_rect("res/carre_gris.png", &rect_bg_pingu, renderer_menu_selection, 1000.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0); 
  SDL_Rect rect_contour_pingu;
  SDL_Texture * texture_contour_pingu = creat_texture_rect("res/carre_perso.png", &rect_contour_pingu, renderer_menu_selection, (1000.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);  

  //image de tinky
  SDL_Rect rect_tinky;
  SDL_Texture * texture_tinky = creat_texture_rect("res/tinky.png", &rect_tinky, renderer_menu_selection, 1400.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_tinky;
  SDL_Texture * texture_bg_tinky = creat_texture_rect("res/carre_gris.png", &rect_bg_tinky, renderer_menu_selection, 1400.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_contour_tinky;
  SDL_Texture * texture_contour_tinky = creat_texture_rect("res/carre_perso.png", &rect_contour_tinky, renderer_menu_selection, (1400.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);  


  //initialisation carrés qui s'affichent derriere le personnage que les joueurs sélectionnent
  //carré rouge de sélection du personnage
  SDL_Rect rect_carre_rouge;
  SDL_Texture * texture_carre_rouge = creat_texture_rect("res/carre_rouge.png", &rect_carre_rouge, renderer_menu_selection, ecran.w+10000, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);

  //carré bleu de sélection du personnage
  SDL_Rect rect_carre_bleu;
  SDL_Texture * texture_carre_bleu = creat_texture_rect("res/carre_bleu.png", &rect_carre_bleu, renderer_menu_selection, ecran.w+10000, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);

  //carré violet de sélection du personnage si les 2 joueurs choissisent le meme
  SDL_Texture * texture_carre_violet = creat_texture_rect("res/carre_violet.png", NULL, renderer_menu_selection, 0, 0, 0, 0);


  //initialisation sprite des personnages

  //sprite de tinky
  /* pas encore créé
  SDL_Surface * surface_sprite_tinky = IMG_Load("res/sprites/Tinky.png");
  SDL_Texture * texture_sprite_Tinky = SDL_CreateTextureFromSurface(renderer_menu_selection, surface_sprite_tinky);
  SDL_FreeSurface(surface_sprite_tinky);
  SDL_Rect rect_sprite_tinky_source;
  SDL_Rect rect_sprite_tinky;

  */

  Joueur j1, j2;
  char j1sprite[50], j2sprite[50];

  SDL_Texture * texture_sprite_shrek = creat_texture_rect("res/sprites/Shrek.png", NULL, renderer_menu_selection, 0, 0, 0, 0);

  SDL_Texture * texture_sprite_goku = creat_texture_rect("res/sprites/Pingutest.png", NULL, renderer_menu_selection, 0, 0, 0, 0);

  SDL_Texture * texture_sprite_pingu = creat_texture_rect("res/sprites/Pingu.png", NULL, renderer_menu_selection, 0, 0, 0, 0);

  TTF_Font* Sans = TTF_OpenFont("res/fonts/Sans.ttf", 24);
  SDL_Color White = {255, 255, 255};
  SDL_Color Grey = {100, 100, 100};
  //bouton jouer
  SDL_Surface* surface_texte_jouer = TTF_RenderText_Solid(Sans, "JOUER", Grey);
  SDL_Texture* texture_texte_jouer = SDL_CreateTextureFromSurface(renderer_menu_selection, surface_texte_jouer);
  SDL_FreeSurface(surface_texte_jouer);
  SDL_Rect rect_texte_jouer;
  rect_texte_jouer.x = 850.0/1920.0*ecran.w;
  rect_texte_jouer.y = 500.0/1080.0*ecran.h;
  rect_texte_jouer.w = 200.0/1920.0*ecran.w;
  rect_texte_jouer.h = 125.0/1080.0*ecran.h;

  SDL_Surface* surface_texte_jouer_white =TTF_RenderText_Solid(Sans, "JOUER", White);
  SDL_Texture* texture_texte_jouer_white = SDL_CreateTextureFromSurface(renderer_menu_selection, surface_texte_jouer_white);
  SDL_FreeSurface(surface_texte_jouer_white);

  //nom des personnages
  /*char * nom_pers_j1=NULL;
  SDL_Surface* surface_texte_pers1 =TTF_RenderText_Solid(Sans,"Texte", White);
  SDL_Texture* texture_texte_pers1 = SDL_CreateTextureFromSurface(renderer_menu_selection, surface_texte_pers1);
  SDL_FreeSurface(surface_texte_pers1);
  SDL_Rect rect_texte_pers1;
  rect_texte_pers1.x = 850.0/1920.0*ecran.w;
  rect_texte_pers1.y = 500.0/1080.0*ecran.h;
  rect_texte_pers1.w = 200.0/1920.0*ecran.w;
  rect_texte_pers1.h = 125.0/1080.0*ecran.h;*/

  /*char * texte2;
  SDL_Surface* surface_texte_texte2 =TTF_RenderText_Solid(Sans,"texte2", Grey);
  SDL_Texture* texture_texte_texte2 = SDL_CreateTextureFromSurface(renderer_menu_selection, surface_texte_texte2);
  SDL_FreeSurface(surface_texte_texte2);
  SDL_Rect rect_texte_texte2;
  rect_texte_texte2.x = 200.0/1920.0*ecran.w;
  rect_texte_texte2.y = 500.0/1080.0*ecran.h;
  rect_texte_texte2.w = 1400.0/1920.0*ecran.w;
  rect_texte_texte2.h = 125.0/1080.0*ecran.h;*/


  j1.texture=NULL;
  j2.texture=NULL;

  int x_button;
  int y_button;
  int tour_joueur=1;
  int sortie=0;
  bool quitter=false;

  SDL_Rect srcrect_bg;
  SDL_Rect dstrect_bg;
  chargerMap(-1, renderer_menu_selection);
  //recherche des actions
  while (!quitter) {

    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
      case SDL_QUIT:
      quitter = true;
      break;
      case SDL_MOUSEBUTTONDOWN:
      x_button =event.button.x;
      y_button =event.button.y;
      //carre 1er pers
      if(x_button>(200.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(200.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
        if(tour_joueur){
          rect_carre_bleu.x = 200.0/1920.0*ecran.w;
          tour_joueur=0;
          j1.texture = texture_sprite_shrek;
          initPerso(&j1, SHREK);
        }else{
          rect_carre_rouge.x = 200.0/1920.0*ecran.w;
          tour_joueur=1;
          j2.texture = texture_sprite_shrek;
          initPerso(&j2, SHREK);
        }
        //carre 2eme pers
      }else if(x_button>(600.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(600.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
        if(tour_joueur){
          rect_carre_bleu.x = 600.0/1920.0*ecran.w;
          tour_joueur=0;
          j1.texture = texture_sprite_goku;
          initPerso(&j1, GOKU);
        }else{
          rect_carre_rouge.x = 600.0/1920.0*ecran.w;
          tour_joueur=1;
          j2.texture = texture_sprite_goku;
          initPerso(&j2, GOKU);
        }
        //carre 3eme pers
      }else if(x_button>(1000.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(1000.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
        if(tour_joueur){
          rect_carre_bleu.x = 1000.0/1920.0*ecran.w;
          tour_joueur=0;
          j1.texture = texture_sprite_pingu;
          initPerso(&j1, PINGU);
        }else{
          rect_carre_rouge.x = 1000.0/1920.0*ecran.w;
          tour_joueur=1;
          j2.texture = texture_sprite_pingu;
          initPerso(&j2, PINGU);
        }
        //carre 4eme pers
      }else if(x_button>(1400.0/1920.0*ecran.w) && y_button>(700.0/1080.0*ecran.h) && x_button<(1400.0/1920.0*ecran.w+ecran.w/6.0) && (y_button<700.0/1080.0*ecran.h+ecran.w/6.0)){
        if(tour_joueur){
          rect_carre_bleu.x = 1400.0/1920.0*ecran.w;
          tour_joueur=0;
          //texture_sprite_j1=texture_sprite_tinky;
        }else{
          rect_carre_rouge.x = 1400.0/1920.0*ecran.w;
          tour_joueur=1;
          //texture_sprite_j2=texture_sprite_tinky;
        }
      } else if(x_button>(850.0/1920.0*ecran.w) && y_button>(500.0/1080.0*ecran.h) && x_button<(850.0/1920.0*ecran.w+200.0/1920.0*ecran.w) && (y_button<500.0/1080.0*ecran.h+125.0/1080.0*ecran.h)){
            if(rect_carre_bleu.x>=0 && rect_carre_bleu.x<=ecran.w && rect_carre_rouge.x>=0 && rect_carre_rouge.x<=ecran.w){
              quitter=true;
              sortie=1;
          }
      }
      break;
      case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_q:
        quitter=true;
        break;
      }
    }
    //affichage de la page
    SDL_RenderClear(renderer_menu_selection);
    //SDL_RenderCopy(renderer_menu_selection, texture_stage_menu_selection, NULL, NULL);
    jouerAnimationBackground(&srcrect_bg, &dstrect_bg);
    renderMap(&srcrect_bg, &dstrect_bg, renderer_menu_selection);

    // carré gris selec perso
    SDL_RenderCopy(renderer_menu_selection, texture_bg_shrek, NULL, &rect_bg_shrek);
    SDL_RenderCopy(renderer_menu_selection, texture_bg_goku, NULL, &rect_bg_goku);
    SDL_RenderCopy(renderer_menu_selection, texture_bg_pingu, NULL, &rect_bg_pingu);
    SDL_RenderCopy(renderer_menu_selection, texture_bg_tinky, NULL, &rect_bg_tinky);

    //affichage des carré de selections
    SDL_RenderCopy(renderer_menu_selection, texture_carre_bleu, NULL, &rect_carre_bleu);
    SDL_RenderCopy(renderer_menu_selection, texture_carre_rouge, NULL, &rect_carre_rouge);
    if(rect_carre_bleu.x == rect_carre_rouge.x){
      SDL_RenderCopy(renderer_menu_selection, texture_carre_violet, NULL, &rect_carre_bleu);
    }

    //affichage de la tete des personnages
    SDL_RenderCopy(renderer_menu_selection, texture_shrek, NULL, &rect_shrek);
    SDL_RenderCopy(renderer_menu_selection, texture_contour_shrek, NULL, &rect_contour_shrek);

    SDL_RenderCopy(renderer_menu_selection, texture_goku, NULL, &rect_goku);
    SDL_RenderCopy(renderer_menu_selection, texture_contour_goku, NULL, &rect_contour_goku);

    SDL_RenderCopy(renderer_menu_selection, texture_pingu, NULL, &rect_pingu);
    SDL_RenderCopy(renderer_menu_selection, texture_contour_pingu, NULL, &rect_contour_pingu);

    SDL_RenderCopy(renderer_menu_selection, texture_tinky, NULL, &rect_tinky);
    SDL_RenderCopy(renderer_menu_selection, texture_contour_tinky, NULL, &rect_contour_tinky);
    //affichage des sprites
    //SDL_RenderCopyEX(renderer_menu_selection, texture_sprite_shrek, &rect_sprite_shrek_source, &rect_sprite_shrek,0,NULL,tour_joueur);
    jouerAnimationPersoMenu(&j1, 1, rect_carre_bleu.x);
    jouerAnimationPersoMenu(&j2, 0, rect_carre_rouge.x);
    SDL_RenderCopyEx(renderer_menu_selection, j1.texture, &(j1.perso.srcrect), &(j1.perso.dstrect), 0, NULL, 1);
    SDL_RenderCopyEx(renderer_menu_selection, j2.texture, &(j2.perso.srcrect), &(j2.perso.dstrect), 0, NULL, 0);

    if(rect_carre_bleu.x>=0 && rect_carre_bleu.x<=ecran.w && rect_carre_rouge.x>=0 && rect_carre_rouge.x<=ecran.w)
      SDL_RenderCopy(renderer_menu_selection, texture_texte_jouer_white, NULL, &rect_texte_jouer);
    else
      SDL_RenderCopy(renderer_menu_selection, texture_texte_jouer, NULL, &rect_texte_jouer);

    SDL_RenderPresent(renderer_menu_selection);
  }
  //sdl destroy texture
  SDL_DestroyTexture(texture_shrek);
  SDL_DestroyTexture(texture_pingu);
  SDL_DestroyTexture(texture_goku);
  SDL_DestroyTexture(texture_tinky);
  SDL_DestroyTexture(texture_carre_rouge);
  SDL_DestroyTexture(texture_carre_bleu);
  SDL_DestroyTexture(texture_carre_violet);
  SDL_DestroyTexture(texture_texte_jouer);
  SDL_DestroyTexture(texture_texte_jouer_white);
  SDL_DestroyTexture(texture_sprite_shrek);
  SDL_DestroyTexture(texture_sprite_goku);
  SDL_DestroyTexture(texture_sprite_pingu);
  SDL_DestroyTexture(texture_contour_shrek);
  SDL_DestroyTexture(texture_contour_goku);
  SDL_DestroyTexture(texture_contour_pingu);
  SDL_DestroyTexture(texture_contour_tinky);
  SDL_DestroyRenderer(renderer_menu_selection);
  SDL_DestroyRenderer(texture_bg_tinky);
  SDL_DestroyWindow(window_menu_selection);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  if(sortie==1)
    initSdl(&j1, &j2);
}