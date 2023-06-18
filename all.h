#ifndef ALL
#define ALL

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_GAME 5

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 120

#define BUTTON_X 50

#define TIME 30000 // 30 seconds
#define REFRESH 20

#define NB_COLOR 9

#define BGC 0
#define YELLOW_COLOR 1
#define GREEN_COLOR 2
#define PURPLE_COLOR 3
#define WHITE_COLOR 4
#define RED_COLOR 5
#define BLUE_COLOR 6
#define BLACK_COLOR 7
#define TRANSPARENT_WHITE_COLOR 8

#define FONT_SIZE 30

typedef struct{
	int score;
    int duree;
} Values_game_simple;

extern SDL_Color *colors;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int st;
extern char** game_title;

extern TTF_Font* font;

int clean_quit();
void dessiner_rect(SDL_Color c, int x, int y, int w, int h);
void baseBg(SDL_Renderer *renderer, int score, int remaining_time, int withoutTime);
void setBg(SDL_Renderer *renderer);
void showInfo(SDL_Renderer *renderer, int score, int remaining_time, int withoutTime);
int main_menu();
void initialisation();
void printOnScreen(const char* chaine, int x, int y);
Values_game_simple* init_game_simple();

#endif
