#ifndef GAME_3
#define GAME_3

#include "all.h"

#define FONT_LETTER_SIZE 256
#define WIDTH_LETTER 114
#define HEIGHT_LETTER 300

typedef struct{
	int score;
    int duree;
} Values_game_3;


Values_game_3* init_game_3();
int play_game_3(SDL_Event game_event,Values_game_3* values,int lettre);
void main_loop_game_3(SDL_Event game_event,Values_game_3* values,SDL_Renderer *renderer);

#endif

