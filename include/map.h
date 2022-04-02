extern float spawnY;
extern int nbFramesMap;
extern int pas;
extern int h_map;
extern int h_map2;
extern int pas2;

#define stage1 0
#define stage2 1
#define stage3 3

void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer);
void chargerMap(int map, SDL_Renderer * renderer, int flag_bg, int drip);
