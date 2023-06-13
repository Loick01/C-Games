#ifndef GAME_1
#define GAME_1

#include "all.h"

#define MIN_SIZE_CIBLE 50
#define MAX_SIZE_CIBLE 200

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 200

#define SPACE_WIDTH WINDOW_WIDTH - (2 * SPACE_X)
#define SPACE_HEIGHT 40
#define SPACE_X 50
#define SPACE_Y 280

#define MIN_SPEED 10
#define MAX_SPEED 15

typedef struct{
	int score;
    int direction; // 1 vers la droite, -1 vers la gauche
    int player_x;
    int duree;
    int wrong;
} Values_game_1;


Values_game_1* init_game_1();
int play_game_1(SDL_Event game_event,Values_game_1* values,SDL_Renderer *renderer,int cible_length,int cible_x,int vitesse);
void main_loop_game_1(SDL_Event game_event,Values_game_1* values,SDL_Renderer *renderer);

#endif

