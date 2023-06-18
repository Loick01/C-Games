#ifndef GAME_5
#define GAME_5

#include "all.h"

#define SPEED 10
#define WIDTH_RECT 50
#define HEIGHT_RECT 50
#define ORD_RECT (WINDOW_HEIGHT - 3*HEIGHT_RECT) 
#define NB_FOE_LINE 6
#define NB_FOE_COLUMN 10

typedef struct{
	SDL_Rect r;
	int position;
} FoeStruct ;

int play_game_5(SDL_Event game_event,SDL_Renderer *renderer,Values_game_simple* values,SDL_Rect *player_rect,int* speed,int* delai_tir,FoeStruct* foes,int* nb_foes);
void main_loop_game_5(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer);
void drawFoes(int* nb_foes,FoeStruct* foes,SDL_Renderer *renderer);

#endif
