#ifndef GAME_2
#define GAME_2

#include "all.h"

#define MIN_SQUARE_SIZE 10
#define MAX_SQUARE_SIZE 120

#define PLAY_AREA_LIMIT 30
#define AUGMENTATION 1

int play_game_2(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer,SDL_Rect cible,SDL_Point point,int* x,int* y);
void main_loop_game_2(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer);

#endif
