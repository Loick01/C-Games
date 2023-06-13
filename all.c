#include "all.h"

void initialisation(){
	SDL_Color bgc = {2, 81, 112, 255};
	SDL_Color button1_color = {230, 146, 21, 255};
	SDL_Color button2_color = {166, 8, 16, 255};
	SDL_Color green_color = {5, 99, 35, 255};
	SDL_Color white_color = {255,255,255,255};
	SDL_Color black_color = {0,0,0,255};
	SDL_Color red_color = {240,20,20,255};
	colors = malloc(sizeof(SDL_Color)*NB_COLOR);
	colors[0] = bgc;
	colors[1] = button1_color;
	colors[2] = button2_color;
	colors[3] = green_color;
	colors[4] = white_color;
	colors[5] = black_color;
	colors[6] = red_color;

	st = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		fprintf(stderr, "Impossible d'initialiser la SDL : %s", SDL_GetError());
		clean_quit();
	}

	window = SDL_CreateWindow("C GAMES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL){
		fprintf(stderr, "Impossible de créer la fenêtre : %s", SDL_GetError());
		clean_quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Impossible de créer le rendu pour la fenêtre : %s", SDL_GetError());
		clean_quit();
	}
}

int clean_quit(){
    if(renderer != NULL){
        SDL_DestroyRenderer(renderer);
    }
    if(window != NULL){
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return st;
}

void dessiner_rect(SDL_Color c, int x, int y, int w, int h){
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &rect);
}

void actualiserWindow(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, colors[BGC].r, colors[BGC].g, colors[BGC].b, colors[BGC].a);
    SDL_RenderClear(renderer);
}

int main_menu(){
	int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));
    SDL_Event menu_event;  
   	SDL_Point point;
   	
   	actualiserWindow(renderer);
   	SDL_SetRenderDrawColor(renderer, colors[BUTTON1_COLOR].r, colors[BUTTON1_COLOR].g, colors[BUTTON1_COLOR].b, colors[BUTTON1_COLOR].a);
    SDL_Rect button1 = {BUTTON_X,100,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button1);
    SDL_SetRenderDrawColor(renderer, colors[BUTTON2_COLOR].r, colors[BUTTON2_COLOR].g, colors[BUTTON2_COLOR].b, colors[BUTTON2_COLOR].a);
    SDL_Rect button2 = {BUTTON_X,350,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button2);
    SDL_RenderPresent(renderer);
    
   	int choix = 0;
    while (choix == 0){	
    	if (SDL_WaitEvent(&menu_event)){
			if(menu_event.type == SDL_QUIT){
				free(x);
				free(y);
				return clean_quit(renderer,window);
			}
			if(menu_event.type == SDL_MOUSEBUTTONDOWN){
				if(menu_event.button.button == SDL_BUTTON_LEFT){
					SDL_GetMouseState(x,y);
					point.x = *x;
					point.y = *y;
					if (SDL_PointInRect(&point,&button1)){
						choix = 1;
					}else if(SDL_PointInRect(&point,&button2)){
						choix = 2;
					}
				}
			}
		}
    }
    free(x);
    free(y);
    return choix;
}


