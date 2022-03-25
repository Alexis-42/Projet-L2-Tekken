#define MENU_PRINCIPAL 0
#define MENU_SELECTION 1
#define MENU_PAUSE 2

void lancerMenu(int menu);
void creerBouton(SDL_Renderer * renderer, TTF_Font * font, char * texte, SDL_Color couleur, SDL_Rect * rect, SDL_Texture ** texture, float x, float y);