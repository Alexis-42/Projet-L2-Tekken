extern float spawnY;
extern int nbFramesMap;
extern int pas;

#define stage1 0
#define stage2 1
#define stage3 3

void renderMap(SDL_Rect * src, SDL_Rect * dst, SDL_Renderer * renderer);
void chargerMap(int map, SDL_Renderer * renderer);
