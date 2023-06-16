#include "all.h"

void initialisation(){
	SDL_Color bgc = {2, 81, 112, 255};
	SDL_Color button1_color = {230, 146, 21, 255};
	SDL_Color button2_color = {166, 8, 16, 255};
	SDL_Color button3_color = {98, 105, 76, 255};
	SDL_Color green_color = {5, 99, 35, 255};
	SDL_Color white_color = {255,255,255,255};
	SDL_Color black_color = {0,0,0,255};
	SDL_Color red_color = {240,20,20,255};
	SDL_Color transparent_white_color = {255,255,255,100};
	colors = malloc(sizeof(SDL_Color)*NB_COLOR);
	colors[0] = bgc;
	colors[1] = button1_color;
	colors[2] = button2_color;
	colors[3] = button3_color;
	colors[4] = green_color;
	colors[5] = white_color;
	colors[6] = black_color;
	colors[7] = red_color;
	colors[8] = transparent_white_color;

	st = EXIT_FAILURE;

	TTF_Init();
	font = TTF_OpenFont("roboto-bold.ttf", FONT_SIZE);
	
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
	TTF_CloseFont(font);
	TTF_Quit();
    SDL_Quit();
    return st;
}

void dessiner_rect(SDL_Color c, int x, int y, int w, int h){
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &rect);
}

void setBg(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, colors[BGC].r, colors[BGC].g, colors[BGC].b, colors[BGC].a);
	SDL_RenderClear(renderer);
}

void showInfo(SDL_Renderer *renderer, int score, int remaining_time, int withoutTime){
	char text[50];
	if(withoutTime){
		sprintf(text, "Score : %d ", score);
	}else{
    	sprintf(text, "Temps restant : %d         Score : %d ", remaining_time/1000, score);
    }

	int width_text, height_text;
    TTF_SizeText(font, text, &width_text, &height_text);
	SDL_Rect infos_rect = {20,WINDOW_HEIGHT-height_text-10,width_text,height_text};
	
	SDL_Surface* surface;
    SDL_Texture* texture;
	surface = TTF_RenderText_Solid(font, text, colors[WHITE_COLOR]); 
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &infos_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void baseBg(SDL_Renderer *renderer, int score, int remaining_time, int withoutTime){
	setBg(renderer);
	showInfo(renderer,score,remaining_time,withoutTime);
}

int main_menu(){
	int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));
    SDL_Event menu_event;  
   	SDL_Point point;
   	
   	setBg(renderer);
   	SDL_SetRenderDrawColor(renderer, colors[BUTTON1_COLOR].r, colors[BUTTON1_COLOR].g, colors[BUTTON1_COLOR].b, colors[BUTTON1_COLOR].a);
    SDL_Rect button1 = {BUTTON_COL1,BUTTON_LINE1,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button1);
    SDL_SetRenderDrawColor(renderer, colors[BUTTON2_COLOR].r, colors[BUTTON2_COLOR].g, colors[BUTTON2_COLOR].b, colors[BUTTON2_COLOR].a);
    SDL_Rect button2 = {BUTTON_COL1,BUTTON_LINE2,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button2);
    SDL_SetRenderDrawColor(renderer, colors[BUTTON3_COLOR].r, colors[BUTTON3_COLOR].g, colors[BUTTON3_COLOR].b, colors[BUTTON3_COLOR].a);
    SDL_Rect button3 = {BUTTON_COL2,BUTTON_LINE1,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button3);
     SDL_SetRenderDrawColor(renderer, colors[BUTTON3_COLOR].r, colors[BUTTON3_COLOR].g, colors[BUTTON3_COLOR].b, colors[BUTTON3_COLOR].a);
    SDL_Rect button4 = {BUTTON_COL2,BUTTON_LINE2,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button4);
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
					}else if(SDL_PointInRect(&point,&button3)){
						choix = 3;
				}else if(SDL_PointInRect(&point,&button4)){
						choix = 4;
					}
				}
			}
		}
    }
    free(x);
    free(y);
    return choix;
}

Values_game_simple* init_game_simple(){
	Values_game_simple* values = malloc(sizeof(Values_game_simple));
	(*values).score = 0;
	(*values).duree = TIME;
	return values;
}

		
		
		

