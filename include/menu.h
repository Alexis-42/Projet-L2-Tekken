#define MENU_PRINCIPAL 0
#define MENU_SELECTION 1
#define MENU_PAUSE 2
#define MENU_OPTIONS 3

void lancerMenu(int menu, int drip, int ia);
void creerBouton(TTF_Font * font, char * texte, SDL_Color couleur, SDL_Rect * rect, SDL_Texture ** texture, float x, float y);
void initFlammes(SDL_Rect * rect, SDL_Texture ** texture, float x, float y);