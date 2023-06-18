#include "all.h"

SDL_Color *colors;
SDL_Window *window;
SDL_Renderer *renderer;
int st;
char** game_title;

TTF_Font* font;

void initialisation(){
	SDL_Color bgc = {2, 81, 112, 255};
	SDL_Color yellow_color = {134, 201, 18, 255};
	SDL_Color green_color = {5, 99, 35, 255};
	SDL_Color purple_color = {77, 13, 61, 255};
	SDL_Color white_color = {255,255,255,255};
	SDL_Color red_color = {240,20,20,255};
	SDL_Color blue_color = {28, 13, 87,255};
	SDL_Color black_color = {0,0,0,255};
	SDL_Color transparent_white_color = {255,255,255,100};
	colors = malloc(sizeof(SDL_Color)*NB_COLOR);
	colors[0] = bgc;
	colors[1] = yellow_color;
	colors[2] = green_color;
	colors[3] = purple_color;
	colors[4] = white_color;
	colors[5] = red_color;
	colors[6] = blue_color;
	colors[7] = black_color;
	colors[8] = transparent_white_color;
	
	game_title = malloc(NB_GAME*sizeof(char*));
	game_title[0] = "SPACE"; // TODO : Charger depuis un fichier
	game_title[1] = "SQUARE";
	game_title[2] = "LETTER";
	game_title[3] = "DODGE";
	game_title[4] = "INVADERS";

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
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, colors[WHITE_COLOR]); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
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
   	SDL_SetRenderDrawColor(renderer, colors[BLUE_COLOR].r, colors[BLUE_COLOR].g, colors[BLUE_COLOR].b, colors[BLUE_COLOR].a);
   	
   	SDL_Rect *buttons = malloc(sizeof(SDL_Rect)*NB_GAME);
   	int button_width = WINDOW_WIDTH - 2*BUTTON_X;
   	int button_height = ((WINDOW_HEIGHT - BUTTON_X) / NB_GAME) - BUTTON_X;
   	for (int i = 0 ; i < NB_GAME ; i++){ // Button for menu
   		SDL_Rect button = {BUTTON_X,BUTTON_X+2*(i*button_height),button_width,button_height };
    	SDL_RenderFillRect(renderer, &button);
    	buttons[i] = button;
    	printOnScreen(game_title[i],BUTTON_X*1.5,BUTTON_X+2*(i*button_height)+BUTTON_X/4);
   	}
   	
    SDL_RenderPresent(renderer);
    
   	int choix = 0;
    while (choix == 0){	
    	if (SDL_WaitEvent(&menu_event)){
			if(menu_event.type == SDL_QUIT){
				free(x);
				free(y);
				return 0;
			}
			if(menu_event.type == SDL_MOUSEBUTTONDOWN){
				if(menu_event.button.button == SDL_BUTTON_LEFT){
					SDL_GetMouseState(x,y);
					point.x = *x;
					point.y = *y;
					for (int i=0 ; i < NB_GAME ; i++){
						if (SDL_PointInRect(&point,&(buttons[i]))){
							choix = ++i;
						}
					}
				}
			}
			
		}
    }
    free(x);
    free(y);
    free(game_title);
    free(buttons);
    return choix;
}

void printOnScreen(const char* text, int x, int y){
	int width_text, height_text;
    TTF_SizeText(font, text, &width_text, &height_text);
	SDL_Rect text_rect = {x,y,width_text,height_text};
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, colors[WHITE_COLOR]); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &text_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

Values_game_simple* init_game_simple(){
	Values_game_simple* values = malloc(sizeof(Values_game_simple));
	(*values).score = 0;
	(*values).duree = TIME;
	return values;
}

		
		
		

