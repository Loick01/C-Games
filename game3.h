#ifndef GAME_3
#define GAME_3

#include "all.h"

#define FONT_LETTER_SIZE 256
#define WIDTH_LETTER 114
#define HEIGHT_LETTER 300
#define NUMBER_FOLLOWING_LETTER 5

typedef struct{
	int score;
    int duree;
    TTF_Font* font_lettre;
    SDL_Rect lettre_rect;
    SDL_Surface* surface_lettre;
    SDL_Texture* texture_lettre;
    
    SDL_Rect next_rect;
    SDL_Surface* next_surfaces_lettres;
    SDL_Texture* next_texture_lettres;
} Values_game_3;



Values_game_3* init_game_3();
int play_game_3(SDL_Event game_event,Values_game_3* values,char* cible,char* next);
void main_loop_game_3(SDL_Event game_event,Values_game_3* values,SDL_Renderer *renderer);

#endif

