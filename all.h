#ifndef ALL
#define ALL

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 120
#define BUTTON_X 250

#define TIME 30000
#define REFRESH 20

#define NB_COLOR 9
#define BGC 0
#define BUTTON1_COLOR 1
#define BUTTON2_COLOR 2
#define BUTTON3_COLOR 3
#define GREEN_COLOR 4
#define WHITE_COLOR 5
#define BLACK_COLOR 6
#define RED_COLOR 7
#define TRANSPARENT_WHITE_COLOR 8

typedef struct{
	int score;
    int duree;
} Values_game_simple;

SDL_Color *colors;
SDL_Window *window;
SDL_Renderer *renderer;
int st;

int clean_quit();
void dessiner_rect(SDL_Color c, int x, int y, int w, int h);
void actualiserWindow(SDL_Renderer *renderer);
int main_menu();
void initialisation();
Values_game_simple* init_game_simple();

#endif
