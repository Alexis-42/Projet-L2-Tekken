/**
 * @file menu_selection.c
 * @author Notelet Léo, Pecquery Charly, Guimbert Alexis
 * @brief fichier qui gère le menu de sélection
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
#include <stdbool.h>
#include "../include/initSdl.h"
#include "../include/menu_principal.h"
#include "../include/jeu.h"
#include "../include/joueur.h"
#include "../include/personnages.h"
#include "../include/animations.h"
#include "../include/map.h"

extern char *text;
extern char *composition;
extern Sint32 cursor;
extern Sint32 selection_len;


/**
 * @brief 
 * 
 * @param chemin_img chemin de l'image
 * @param rect rectangle de la texture
 * @param renderer stocke les textures
 * @param x coordonée x du rectangle
 * @param y coordonée y du rectangle
 * @param w largeur du rectangle
 * @param h hauteur du rectangle
 * @return SDL_Texture* 
 */
  SDL_Texture * creat_texture_rect(char * chemin_img, SDL_Rect * rect, SDL_Renderer * renderer, float x, float y, float w, float h){
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

/**
 * @brief fonction qui permet d'afficher le personnage que l'on a choisi dans le menu, celui ci danse
 * 
 * @param joueur structure du personnage choisi
 * @param tour variable permettant de savoir si le personnage appartient au joueur 1 ou 2
 */
void jouerAnimationPersoMenu(Joueur * joueur, int tour){ //Pour freezer l'anim il faut anuller le getTick
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

srcrect.x = sprite * 540;
srcrect.y = 0;
srcrect.w = joueur->perso.taille_perso.w/joueur->perso.taille_perso.mult;
srcrect.h = joueur->perso.taille_perso.h/joueur->perso.taille_perso.mult;

dstrect.x = posx/1920*ecran.w;
dstrect.y = 300/1080.0*ecran.h;
dstrect.w = joueur->perso.taille_perso.w/joueur->perso.taille_perso.mult;
dstrect.h = joueur->perso.taille_perso.h/joueur->perso.taille_perso.mult;

joueur->perso.srcrect=srcrect;
joueur->perso.dstrect=dstrect;
}

/**
 * @brief fonction qui gère le menu de sélection des personnages et des cartes
 * 
 * @param drip option d'affichage
 * @param ia variable qui vérifie si l'on est en joueur contre joueur ou joueur contre IA
 */
void menu_selection(int drip, int ia){
  int num_map=1;
  SDL_Rect srcBg;

  //initialisation de sdl
  if(TTF_Init()==-1){
    printf("librairie non initialisé");
    exit(EXIT_FAILURE);
  }

  SDL_Texture ** texture_preview = malloc(sizeof(SDL_Texture *)*12);
  texture_preview[0] = creat_texture_rect("res/selection/secret.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[1] = creat_texture_rect("res/backgrounds/stage1.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[2] = creat_texture_rect("res/backgrounds/stage2.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[3] = creat_texture_rect("res/backgrounds/stage3.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[4] = creat_texture_rect("res/backgrounds/stage4.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[5] = creat_texture_rect("res/backgrounds/stage5.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[6] = creat_texture_rect("res/backgrounds/stage6.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[7] = creat_texture_rect("res/backgrounds/stage7.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[8] = creat_texture_rect("res/backgrounds/stage8.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[9] = creat_texture_rect("res/backgrounds/stage9.png", NULL, renderer, 0, 0, 0, 0);
  texture_preview[10] = creat_texture_rect("res/backgrounds/stage10.png", NULL, renderer, 0, 0, 0, 0);
  if(drip)
    texture_preview[11] = creat_texture_rect("res/backgrounds/stage11.png", NULL, renderer, 0, 0, 0, 0);
//fond des fonds d écran en preview
  SDL_Rect rect_bg_map_fond;
  SDL_Texture * texture_fond_bg_preview = creat_texture_rect("res/selection/carre_perso.png",&rect_bg_map_fond, renderer,ecran.w/4.0-10.0, 250.0/1080.0*(ecran.h/4.5)-10.0, ecran.w/2.0+20.0, ecran.w/5.0+20.0);

  //preparation image des personnages
  //image de shrek
  SDL_Rect rect_shrek;
  SDL_Texture * texture_shrek;
  if(drip)
    texture_shrek = creat_texture_rect("res/selection/shrekdrip.png", &rect_shrek, renderer, 200.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  else
    texture_shrek = creat_texture_rect("res/selection/shrek.png", &rect_shrek, renderer, 200.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_shrek;
  SDL_Texture * texture_bg_shrek = creat_texture_rect("res/selection/carre_gris.png", &rect_bg_shrek, renderer, 200.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_contour_shrek;
  SDL_Texture * texture_contour_shrek = creat_texture_rect("res/selection/carre_perso.png", &rect_contour_shrek, renderer, (200.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);

  //image de goku
  SDL_Rect rect_goku;
  SDL_Texture * texture_goku;
  if(drip)
    texture_goku = creat_texture_rect("res/selection/gokudrip.png", &rect_goku, renderer, 600.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  else
    texture_goku = creat_texture_rect("res/selection/goku.png", &rect_goku, renderer, 600.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_goku;
  SDL_Texture * texture_bg_goku = creat_texture_rect("res/selection/carre_gris.png", &rect_bg_goku, renderer, 600.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);

  SDL_Rect rect_contour_goku;
  SDL_Texture * texture_contour_goku = creat_texture_rect("res/selection/carre_perso.png", &rect_contour_goku, renderer, (600.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);

  //image de pingu
  SDL_Rect rect_pingu;
  SDL_Texture * texture_pingu;
  if(drip)
    texture_pingu= creat_texture_rect("res/selection/pingudrip.png", &rect_pingu, renderer, 1000.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  else
    texture_pingu = creat_texture_rect("res/selection/pingu.png", &rect_pingu, renderer, 1000.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_pingu;
  SDL_Texture * texture_bg_pingu = creat_texture_rect("res/selection/carre_gris.png", &rect_bg_pingu, renderer, 1000.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_contour_pingu;
  SDL_Texture * texture_contour_pingu = creat_texture_rect("res/selection/carre_perso.png", &rect_contour_pingu, renderer, (1000.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);

  //image de tinky
  SDL_Rect rect_tinky;
  SDL_Texture * texture_tinky;
  if(drip)
    texture_tinky = creat_texture_rect("res/selection/mickeydrip.png", &rect_tinky, renderer, 1400.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  else
    texture_tinky = creat_texture_rect("res/selection/mickey.png", &rect_tinky, renderer, 1400.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_bg_tinky;
  SDL_Texture * texture_bg_tinky = creat_texture_rect("res/selection/carre_gris.png", &rect_bg_tinky, renderer, 1400.0/1920.0*ecran.w, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);
  SDL_Rect rect_contour_tinky;
  SDL_Texture * texture_contour_tinky = creat_texture_rect("res/selection/carre_perso.png", &rect_contour_tinky, renderer, (1400.0-(0.009*ecran.w))/1920.0*ecran.w, (700.0-(0.009*ecran.w))/1080.0*ecran.h, (ecran.w+(0.063*ecran.w))/6.0, (ecran.w+(0.063*ecran.w))/6.0);


  //initialisation carrés qui s'affichent derriere le personnage que les joueurs sélectionnent
  //carré rouge de sélection du personnage
  SDL_Rect rect_carre_rouge;
  SDL_Texture * texture_carre_rouge = creat_texture_rect("res/selection/carre_rouge.png", &rect_carre_rouge, renderer, ecran.w+10000, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);

  //carré bleu de sélection du personnage
  SDL_Rect rect_carre_bleu;
  SDL_Texture * texture_carre_bleu = creat_texture_rect("res/selection/carre_bleu.png", &rect_carre_bleu, renderer, ecran.w+10000, 700.0/1080.0*ecran.h, ecran.w/6.0, ecran.w/6.0);

  //carré violet de sélection du personnage si les 2 joueurs choissisent le meme
  SDL_Texture * texture_carre_violet = creat_texture_rect("res/selection/carre_violet.png", NULL, renderer, 0, 0, 0, 0);

  Joueur j1, j2;

  SDL_Texture * texture_sprite_shrek = creat_texture_rect("res/sprites/Shrek.png", NULL, renderer, 0, 0, 0, 0);

  SDL_Texture * texture_sprite_goku = creat_texture_rect("res/sprites/Goku.png", NULL, renderer, 0, 0, 0, 0);

  SDL_Texture * texture_sprite_pingu = creat_texture_rect("res/sprites/Pingu.png", NULL, renderer, 0, 0, 0, 0);

  SDL_Texture * texture_sprite_mickey = creat_texture_rect("res/sprites/Mickey.png", NULL, renderer, 0, 0, 0, 0);

  TTF_Font* Sans = TTF_OpenFont("res/fonts/Sans.ttf", 24);
  SDL_Color White = {255, 255, 255};
  SDL_Color Grey = {100, 100, 100};
  //bouton jouer
  SDL_Surface* surface_texte_jouer = TTF_RenderText_Solid(Sans, "JOUER", Grey);
  SDL_Texture* texture_texte_jouer = SDL_CreateTextureFromSurface(renderer, surface_texte_jouer);
  SDL_FreeSurface(surface_texte_jouer);
  SDL_Rect rect_texte_jouer;
  rect_texte_jouer.x = 850.0/1920.0*ecran.w;
  rect_texte_jouer.y = 500.0/1080.0*ecran.h;
  rect_texte_jouer.w = 200.0/1920.0*ecran.w;
  rect_texte_jouer.h = 125.0/1080.0*ecran.h;

  SDL_Surface* surface_texte_jouer_white =TTF_RenderText_Solid(Sans, "JOUER", White);
  SDL_Texture* texture_texte_jouer_white = SDL_CreateTextureFromSurface(renderer, surface_texte_jouer_white);
  SDL_FreeSurface(surface_texte_jouer_white);


  /* AFFICHAGE RELATIF A LA SELECTION DE MAP */
  SDL_Rect rect_bg_map;
  rect_bg_map.x = ecran.w/4;
  rect_bg_map.y = 250/1080.0*(ecran.h/4.5);
  rect_bg_map.w = ecran.w/2;
  rect_bg_map.h = ecran.w/5.0;

  SDL_Rect rect_bouton_gauche;
  SDL_Texture * texture_bouton_gauche = creat_texture_rect("res/selection/bouton_gauche.png", &rect_bouton_gauche, renderer, (rect_bg_map.x-ecran.w/14.0)-(ecran.w/100), 700.0/1080.0*(ecran.h/4.5), ecran.w/14.0, ecran.w/14.0);

  SDL_Rect rect_bouton_droit;
  SDL_Texture * texture_bouton_droit = creat_texture_rect("res/selection/bouton_droit.png", &rect_bouton_droit, renderer, rect_bg_map.x+rect_bg_map.w+(ecran.w/100), 700.0/1080.0*(ecran.h/4.5), ecran.w/14.0, ecran.w/14.0);

  j1.texture=NULL;
  j2.texture=NULL;

  int x_button;
  int y_button;
  int tour_joueur=1;
  int sortie=0;
  bool quitter=false;

  SDL_Rect srcrect_bg;
  SDL_Rect dstrect_bg;
  chargerMap(-1, renderer,1,drip);
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
          j1.texture = texture_sprite_mickey;
          initPerso(&j1, MICKEY);
        }else{
          rect_carre_rouge.x = 1400.0/1920.0*ecran.w;
          tour_joueur=1;
          j2.texture = texture_sprite_mickey;
          initPerso(&j2, MICKEY);
        }
      } else if(x_button>(850.0/1920.0*ecran.w) && y_button>(500.0/1080.0*ecran.h) && x_button<(850.0/1920.0*ecran.w+200.0/1920.0*ecran.w) && (y_button<500.0/1080.0*ecran.h+125.0/1080.0*ecran.h)){
            if(rect_carre_bleu.x>=0 && rect_carre_bleu.x<=ecran.w && rect_carre_rouge.x>=0 && rect_carre_rouge.x<=ecran.w){
              quitter=true;
              sortie=1;
          }
      }else if(x_button>rect_bouton_gauche.x && x_button<(rect_bouton_gauche.x+rect_bouton_gauche.w) && y_button>rect_bouton_gauche.y && y_button<(rect_bouton_gauche.y+rect_bouton_gauche.h)){
        // bouton gauche
        if(num_map == 1){
          if(drip)
            num_map=11;
          else
            num_map = 10;
        }
        else
          num_map = ( num_map ) - 1;
      }else if(x_button>rect_bouton_droit.x && x_button<(rect_bouton_droit.x+rect_bouton_droit.w) && y_button>rect_bouton_droit.y && y_button<(rect_bouton_droit.y+rect_bouton_droit.h)){
        // bouton droit
        if(drip)
          num_map = ( num_map % 11 ) + 1;
        else
          num_map = ( num_map % 10 ) + 1;
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
    SDL_RenderClear(renderer);
    jouerAnimationBackground(&srcrect_bg, &dstrect_bg,1);
    renderMap(&srcrect_bg, &dstrect_bg, renderer);

    // carré gris selec perso
    SDL_RenderCopy(renderer, texture_bg_shrek, NULL, &rect_bg_shrek);
    SDL_RenderCopy(renderer, texture_bg_goku, NULL, &rect_bg_goku);
    SDL_RenderCopy(renderer, texture_bg_pingu, NULL, &rect_bg_pingu);
    SDL_RenderCopy(renderer, texture_bg_tinky, NULL, &rect_bg_tinky);

    //affichage des carré de selections
    SDL_RenderCopy(renderer, texture_carre_bleu, NULL, &rect_carre_bleu);
    SDL_RenderCopy(renderer, texture_carre_rouge, NULL, &rect_carre_rouge);
    if(rect_carre_bleu.x == rect_carre_rouge.x){
      SDL_RenderCopy(renderer, texture_carre_violet, NULL, &rect_carre_bleu);
    }

    //affichage de la tete des personnages
    SDL_RenderCopy(renderer, texture_shrek, NULL, &rect_shrek);
    SDL_RenderCopy(renderer, texture_contour_shrek, NULL, &rect_contour_shrek);

    SDL_RenderCopy(renderer, texture_goku, NULL, &rect_goku);
    SDL_RenderCopy(renderer, texture_contour_goku, NULL, &rect_contour_goku);

    SDL_RenderCopy(renderer, texture_pingu, NULL, &rect_pingu);
    SDL_RenderCopy(renderer, texture_contour_pingu, NULL, &rect_contour_pingu);

    SDL_RenderCopy(renderer, texture_tinky, NULL, &rect_tinky);
    SDL_RenderCopy(renderer, texture_contour_tinky, NULL, &rect_contour_tinky);
    //affichage des sprites
    //SDL_RenderCopyEX(renderer, texture_sprite_shrek, &rect_sprite_shrek_source, &rect_sprite_shrek,0,NULL,tour_joueur);
    jouerAnimationPersoMenu(&j1, 1, rect_carre_bleu.x);
    jouerAnimationPersoMenu(&j2, 0, rect_carre_rouge.x);
    SDL_RenderCopyEx(renderer, j1.texture, &(j1.perso.srcrect), &(j1.perso.dstrect), 0, NULL, 1);
    SDL_RenderCopyEx(renderer, j2.texture, &(j2.perso.srcrect), &(j2.perso.dstrect), 0, NULL, 0);

    if(rect_carre_bleu.x>=0 && rect_carre_bleu.x<=ecran.w && rect_carre_rouge.x>=0 && rect_carre_rouge.x<=ecran.w)
      SDL_RenderCopy(renderer, texture_texte_jouer_white, NULL, &rect_texte_jouer);
    else
      SDL_RenderCopy(renderer, texture_texte_jouer, NULL, &rect_texte_jouer);

    chargerMap(num_map, NULL,0,drip);
    jouerAnimationBackground(&srcBg,NULL,0);
    SDL_RenderCopy(renderer, texture_preview[num_map], &srcBg, &rect_bg_map); 
    SDL_RenderCopy(renderer, texture_bouton_gauche, NULL, &rect_bouton_gauche);
    SDL_RenderCopy(renderer, texture_bouton_droit, NULL, &rect_bouton_droit);
    SDL_RenderCopy(renderer, texture_fond_bg_preview,NULL, &rect_bg_map_fond);
    SDL_RenderPresent(renderer);
  }
  /* destruction des texture */
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
  SDL_DestroyTexture(texture_bouton_gauche);
  SDL_DestroyTexture(texture_bouton_droit);
  SDL_DestroyTexture(texture_bg_shrek);
  SDL_DestroyTexture(texture_bg_goku);
  SDL_DestroyTexture(texture_bg_pingu);
  SDL_DestroyTexture(texture_bg_tinky);
  //a voir
  SDL_DestroyTexture(texture_fond_bg_preview);
  int max=10;
  if(drip)
    max = 11;
  for(int i=1; i<=max; i++)
      SDL_DestroyTexture(texture_preview[i]);
  free(texture_preview);
  //SDL_DestroyTexture();
  TTF_Quit();
  if(sortie==1)
    initSdl(&j1, &j2, num_map,drip,ia);
}
