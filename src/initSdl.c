#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <time.h>
#include "../include/initSdl.h"
#include "../include/mouvements.h"
#include "../include/menu.h"
#include "../include/joueur.h"
#include "../include/animations.h"
#include "../include/jeu.h"
#include "../include/personnages.h"
#include "../include/map.h"
#include "../include/gui.h"
#include "../include/pause.h"
#include "../include/ia.h"
#include "../include/options.h"

int sec_deb_combat, temps_combat, ancien_temps=-1, temps_deb_pause, temps_fin_pause, temps_pause;
bool quit;
bool pause=false;
SDL_DisplayMode ecran;
int flag_perdu=0;
int numRound=0;
SDL_Color blanc = {255, 255, 255};

/**
 * @brief Fonction permettant d'assombrir l'écran et d'annoncer le joueur gagnant
 * 
 * @param joueurGagnant Joueur qui à gagné le round
 * @param joueurPerdant Joueur qui à perdu le round
 * @param font font passée en paramètre pour afficher le nom du joueur gagnant
 */
void roundSuivant(Joueur * j1, Joueur * j2 ,TTF_Font * font){
  SDL_Texture * texture = NULL;
  SDL_Rect rect;
  char texte[50];
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);

  Joueur * joueurGagnant = NULL; 
  if(j1->vie > j2->vie){
    j1->roundsGagnes++;
    joueurGagnant=j1;
  }else if(j1->vie < j2->vie){
    j2->roundsGagnes++;
    joueurGagnant=j2;
  }

  if(joueurGagnant == NULL){
    snprintf(texte, sizeof(texte), "Egalite !");
    flag_perdu=0;
    initJoueur(j1, 100.0, j1->texture, gauche);
    initJoueur(j2, 600.0, j2->texture, droite);
    creerBouton(font, texte, blanc, &rect, &texture, ecran.w/2-250, ecran.h/2-100);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    return;
  }

  if(joueurGagnant->roundsGagnes<nbreRoundsMax){
    numRound++;

    snprintf(texte, sizeof(texte), "%s gagne le round %d !", joueurGagnant->perso.nom, numRound);
    
    flag_perdu=0;
    initJoueur(j1, 100.0, j1->texture, gauche);
    initJoueur(j2, 600.0, j2->texture, droite);
    creerBouton(font, texte, blanc, &rect, &texture, ecran.w/2-250, ecran.h/2-100);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
  } else {
    snprintf(texte, sizeof(texte), "Match termine ! %s gagne la partie !", joueurGagnant->perso.nom);
    joueurGagnant->action=DANSE;
    creerBouton(font, texte, blanc, &rect, &texture, ecran.w/2-250, ecran.h/2-100);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    numRound=0;
    flag_perdu=0;
    sortie=2;
    quit=true;
  }
}

/**
 * @brief Fonction qui boucle tant qu'un des deux joueurs n'a pas gagné le nombre de rounds suffisant
 * 
 * @param j1 Structure représentant le joueur 1
 * @param j2 Structure représentant le joueur 2
 * @param num_map entier représentant le numéro de la map choisie
 * @param drip entier qui vaut 1 si secret activé et 2 si mode debug activé
 * @param ia entier qui vaut 1 si le mode ia est activé ou 0 si en multi local
 */
void initSdl(Joueur * j1, Joueur * j2, int num_map, int drip, int ia) {
  quit=false;
  srand(time(NULL));
  temps_combat = 0;
  sec_deb_combat = 0;
  temps_fin_pause = 0;
  temps_deb_pause = 0;
  temps_pause = 0;
  SDL_Surface * surface_hitbox_coupj1 = IMG_Load("res/rectangle_bleu.png");
  SDL_Texture * texture_hitbox_coupj1;
  SDL_Surface * surface_hitbox_coupj2 = IMG_Load("res/rectangle_bleu.png");
  SDL_Texture * texture_hitbox_coupj2;
  SDL_Surface * surface_hitbox_piedj1 = IMG_Load("res/rectangle_rouge.png");
  SDL_Texture * texture_hitbox_piedj1;
  SDL_Surface * surface_hitbox_piedj2 = IMG_Load("res/rectangle_rouge.png");
  SDL_Texture * texture_hitbox_piedj2;
  SDL_Texture * tex_menu_Principal = NULL;
  SDL_Texture * texture_carre_jaune = NULL;
  SDL_Texture * texture_carre_rouge = NULL;
  SDL_Texture * texture_barre_de_vie = NULL;
  SDL_Texture * texture_nomj1 = NULL;
  SDL_Texture * texture_nomj2 = NULL;
  SDL_Texture * texture_temps = NULL;
  SDL_Texture * j1Txt_texture = NULL, * j2Txt_texture = NULL;
  SDL_Rect srcBg, dstBg, rect_sprite_pv_j1, rect_sprite_pv_j2,rect_nom_j1, rect_nom_j2,rect_temps;
  SDL_Rect j1Txt_rect, j2Txt_rect; //Rectangles des textes J1 et J2 au dessus des joueurs

  texture_hitbox_coupj1 = SDL_CreateTextureFromSurface(renderer, surface_hitbox_coupj1);
  texture_hitbox_coupj2 = SDL_CreateTextureFromSurface(renderer, surface_hitbox_coupj2);

  texture_hitbox_piedj1 = SDL_CreateTextureFromSurface(renderer, surface_hitbox_piedj1);
  texture_hitbox_piedj2 = SDL_CreateTextureFromSurface(renderer, surface_hitbox_piedj2);

  char j1sprite[50], j2sprite[50];
  snprintf(j1sprite, sizeof(j1sprite), "res/sprites/%s.png", j1->perso.nom);
  snprintf(j2sprite, sizeof(j2sprite), "res/sprites/%s.png", j2->perso.nom);

  SDL_Surface * perso1 = IMG_Load(j1sprite);
  SDL_Surface * perso2 = IMG_Load(j2sprite);

  chargerMap(num_map, renderer, 1, drip);

  SDL_Texture * texture_joueur1 = SDL_CreateTextureFromSurface(renderer, perso1);
  SDL_Texture * texture_joueur2 = SDL_CreateTextureFromSurface(renderer, perso2);
  SDL_FreeSurface(perso1);
  SDL_FreeSurface(perso2);

  TTF_Init();

  initJoueur(j1, 100.0, texture_joueur1, gauche);
  initJoueur(j2, 600.0, texture_joueur2, droite);
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0); //Couleur des hitboxes

  init_sprite_pv(&rect_sprite_pv_j1, 1);
  init_sprite_pv(&rect_sprite_pv_j2, 2);

  SDL_Surface * sprite_barre_de_vie = IMG_Load("res/barre_de_vie.png");
  init_gui(&texture_carre_jaune, &texture_carre_rouge, sprite_barre_de_vie, &texture_barre_de_vie);

  TTF_Font * font = NULL;
  font = TTF_OpenFont("res/fonts/Sans.ttf", 50);

  init_afficher_nom_joueur(j1, font, &rect_sprite_pv_j1, &rect_nom_j1, &texture_nomj1,1);
  init_afficher_nom_joueur(j2, font, &rect_sprite_pv_j2, &rect_nom_j2, &texture_nomj2,2);
  creerBouton(font, "J1", blanc, &j1Txt_rect, &j1Txt_texture, 0, 0);
  if(ia){
    creerBouton(font, "IA", blanc, &j2Txt_rect, &j2Txt_texture, 0, 0);
  }else
  creerBouton(font, "J2", blanc, &j2Txt_rect, &j2Txt_texture, 0, 0);
  
  int temps_parerJ1=0;
  int temps_parerJ2=0;

  initPause();

  int sec_anim;
  sec_deb_combat = SDL_GetTicks()/1000;
  int tmp=-1;
//boucle du jeu
  while (!quit) {
    if(SDL_GetTicks()%20==0){
      SDL_Event event;
      SDL_PollEvent(&event);
      
      sec_anim = SDL_GetTicks()/75;
      jouerAnimationBackground(&srcBg, &dstBg,1);
      
      j1Txt_rect.x = j1->hitbox.x+j1->hitbox.w/2;
      j1Txt_rect.y = j1->position.y;

      j2Txt_rect.x = j2->hitbox.x+j2->hitbox.w/2;
      j2Txt_rect.y = j2->position.y;

      switch (event.type) {
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              if(!pause){
                temps_deb_pause = (SDL_GetTicks());
              }else if(pause){
                temps_fin_pause = (SDL_GetTicks());
                temps_pause+=(temps_fin_pause - temps_deb_pause)/1000;
                if(debug)
                  printf("\ntemps de la pause : %d\ttemps de la pause total : %d",(temps_fin_pause - temps_deb_pause)/1000,temps_pause);
              }
                pause = !pause;
              
            break;
          }
        case SDL_MOUSEBUTTONDOWN:
          if(event.button.x>=btn1.x && event.button.y>=btn1.y && event.button.x<=btn1.w+btn1.x && event.button.y<=btn1.y+btn1.h && pause){
            temps_fin_pause = (SDL_GetTicks());
            temps_pause+=(temps_fin_pause - temps_deb_pause)/1000;
            if(debug)
              printf("\ntemps de la pause : %d\ttemps de la pause total : %d",(temps_fin_pause - temps_deb_pause)/1000,temps_pause);
            pause = !pause;
          }
      }

      if(!pause)
        temps_combat = SDL_GetTicks()/1000 - temps_pause - sec_deb_combat;


      if(temps_combat!=tmp){
        if(debug){
          printf("\ntemps du jeu : %d\ttemp en tick : %d",temps_combat,SDL_GetTicks()/1000);
          printf("\npoint de vie j1 : %d\tpoint de vie j2 : %d",j1->vie,j2->vie);
        }
        tmp=temps_combat;
      }

      sauter(j1);
      sauter(j2);
      jouerAnimation(j1,sec_anim,j2);
      jouerAnimation(j2,sec_anim,j1);

      if(j1->perso.frame==0){
        jouerAnimationContinu(j1,sec_anim);
      }
      if(j2->perso.frame==0){
        jouerAnimationContinu(j2,sec_anim);
      }

      flag_perdu = checkPerdu(j1, j2);
      if(!flag_perdu)
        SDL_RenderClear(renderer);
      renderMap(&srcBg, &dstBg, renderer);

      hitbox(j1, texture_hitbox_coupj1,1);
      hitbox(j2, texture_hitbox_coupj2,1);
      hitbox(j1, texture_hitbox_piedj1,0);
      hitbox(j2, texture_hitbox_piedj2,0);

      if(debug){
        SDL_RenderFillRect(renderer, &(j1->hitbox));
        SDL_RenderFillRect(renderer, &(j2->hitbox));
      }
      renderAnimation(j1);
      renderAnimation(j2);
      barre_de_vie(j1, &rect_sprite_pv_j1, texture_barre_de_vie, texture_carre_rouge, texture_carre_jaune, font);
      barre_de_vie(j2, &rect_sprite_pv_j2, texture_barre_de_vie, texture_carre_rouge, texture_carre_jaune, font);
      
      init_affichage_temps(temps_combat, font, &rect_sprite_pv_j1, &texture_temps, &rect_temps);

      SDL_RenderCopy(renderer, texture_temps, NULL ,&rect_temps);

      SDL_DestroyTexture(texture_temps);

      SDL_RenderCopy(renderer, texture_nomj1, NULL ,&rect_nom_j1);
      SDL_RenderCopy(renderer, texture_nomj2, NULL ,&rect_nom_j2);
      SDL_RenderFillRect(renderer, &j1Txt_rect);
      SDL_RenderFillRect(renderer, &j2Txt_rect);

      SDL_RenderCopy(renderer, j1Txt_texture, NULL, &j1Txt_rect);
      SDL_RenderCopy(renderer, j2Txt_texture, NULL, &j2Txt_rect);

      checkmort(j1,j2);

      if(!pause){
        deplacements(j1, j2, &event, ia, &temps_parerJ2, &temps_parerJ1);
        if(ia){
          deplacements_ia(j2,j1);
        }
      }
      else {
        selectionPause(event, drip,ia);
        renderPause();
      }

    if(flag_perdu == 1 && j1->perso.frame+1>=j1->perso.nb_frame[MORT]){
    temps_pause=0;
    sec_deb_combat = SDL_GetTicks()/1000;
    roundSuivant(j1, j2, font);
  } else if(flag_perdu == 2 && j2->perso.frame+1>=j2->perso.nb_frame[MORT]){
    temps_pause=0;
    sec_deb_combat = SDL_GetTicks()/1000;
    roundSuivant(j1, j2, font);
  }else if(temps_combat>=60){
    temps_pause=0;
    sec_deb_combat = SDL_GetTicks()/1000;
    roundSuivant(j1, j2, font);
  }
    SDL_RenderPresent(renderer);
  }

  }

  SDL_RenderClear(renderer);
  
  /* free les textures */
  SDL_DestroyTexture(texture_hitbox_coupj1);
  SDL_DestroyTexture(texture_hitbox_coupj2);
  SDL_DestroyTexture(texture_nomj1);
  SDL_DestroyTexture(texture_nomj2);
  SDL_DestroyTexture(texture_carre_rouge);
  SDL_DestroyTexture(texture_carre_jaune);
  SDL_DestroyTexture(texture_barre_de_vie);
  SDL_DestroyTexture(tex_menu_Principal);
  SDL_DestroyTexture(texture_joueur1);
  SDL_DestroyTexture(texture_joueur2);
  SDL_DestroyTexture(j1Txt_texture);
  SDL_DestroyTexture(j2Txt_texture);

  /* free les surfaces */
  SDL_FreeSurface(sprite_barre_de_vie);
  SDL_FreeSurface(surface_hitbox_coupj1);
  SDL_FreeSurface(surface_hitbox_coupj2);
  SDL_FreeSurface(surface_hitbox_piedj1);
  SDL_FreeSurface(surface_hitbox_piedj2);

  /* free le reste */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  if(sortie==2){
    lancerMenu(MENU_PRINCIPAL,drip,ia);
  }
}
