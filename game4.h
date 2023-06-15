#ifndef GAME_4
#define GAME_4

#include "all.h"

#define WIDTH_PLAYER 50
#define HEIGHT_PLAYER 50
#define NB_RECT_DODGE 5
#define AWAY_FROM_WINDOW 100
#define INITIAL_SPEED 5
#define BASE_FRAME 35

int play_game_4(SDL_Event game_event,SDL_Renderer *renderer,SDL_Rect *player_rect,SDL_Rect to_dodge, int *nb_frame,int* speed);
void main_loop_game_4(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer);

#endif
