#include "defs.h"

typedef struct Map
{
	char *filename;
	int startX, startY;
	int maxX, maxY;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	SDL_Surface *background;
} Map;

typedef struct Input
{
	int left, right, up, down, jump;
} Input;

typedef struct Entity
{
	int w, h, onGround;
	int thinkTime;
	float x, y, dirX, dirY;
} Entity;
