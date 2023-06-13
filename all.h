#ifndef ALL
#define ALL

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 150
#define BUTTON_X 250

#define TIME 30000
#define REFRESH 20

#define NB_COLOR 7
#define BGC 0
#define BUTTON1_COLOR 1
#define BUTTON2_COLOR 2
#define GREEN_COLOR 3
#define WHITE_COLOR 4
#define BLACK_COLOR 5
#define RED_COLOR 6


SDL_Color *colors;
SDL_Window *window;
SDL_Renderer *renderer;
int st;

int clean_quit();
void dessiner_rect(SDL_Color c, int x, int y, int w, int h);
void actualiserWindow(SDL_Renderer *renderer);
int main_menu();
void initialisation();

#endif
