#ifndef GAME_5
#define GAME_5

#include "all.h"

#define SPEED 10
#define WIDTH_RECT 50
#define HEIGHT_RECT 50
#define ORD_RECT (WINDOW_HEIGHT - 3*HEIGHT_RECT) 
#define NB_FOE_LINE 6
#define NB_FOE_COLUMN 10

#define WIDTH_TIR 10
#define HEIGHT_TIR 30
#define SPEED_TIR 15

typedef struct{
	SDL_Rect r;
	int position;
} FoeStruct ;

typedef struct{
	int score;
    int duree;
    int speed;
    SDL_Rect *player_rect;
    int delai_tir;
    FoeStruct** foes;
    SDL_Rect** tirs;
    int nb_tirs;
    FoeStruct** direct_foes;
} Values_game_5 ;

Values_game_5* init_game_5();
int play_game_5(SDL_Event game_event,SDL_Renderer *renderer,Values_game_5* values);
void main_loop_game_5(SDL_Event game_event,Values_game_5* values,SDL_Renderer *renderer);
void drawFoes(FoeStruct** foes,SDL_Renderer *renderer);

#endif
