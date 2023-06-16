#ifndef GAME_4
#define GAME_4

#include "all.h"

#define WIDTH_RECT 50
#define HEIGHT_RECT 50
#define NB_RECT_DODGE 50
#define INITIAL_SPEED 5

typedef struct{
	SDL_Rect r;
	int dir_x;
	int dir_y;
	int lifetime;
} Rect_Struct;

int play_game_4(SDL_Event game_event,SDL_Renderer *renderer,Values_game_simple* values,SDL_Rect *player_rect,int* speed,int* nb_rect_dodge,Rect_Struct** rect_dodge);
void main_loop_game_4(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer);

#endif
