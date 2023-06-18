#include "game5.h"

void drawFoes(int* nb_foes,FoeStruct* foes,SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, colors[RED_COLOR].r, colors[RED_COLOR].g, colors[RED_COLOR].b, colors[RED_COLOR].a);
	for (int i = 0; i < *nb_foes ; i++){
		SDL_RenderFillRect(renderer, &(foes[i].r));
	}
}

int play_game_5(SDL_Event game_event,SDL_Renderer *renderer,Values_game_simple* values,SDL_Rect *player_rect,int* speed,int* delai_tir,FoeStruct* foes,int* nb_foes){
	while (SDL_PollEvent(&game_event)){
		if(game_event.type == SDL_QUIT){
			return 0;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL); 
	if (state[SDL_SCANCODE_D] && player_rect->x + WIDTH_RECT <= WINDOW_WIDTH) {
 		player_rect->x += *speed;
	}
	if (state[SDL_SCANCODE_A] && player_rect->x >= 0) {
 		player_rect->x -= *speed;
	}
	if (state[SDL_SCANCODE_SPACE] && *delai_tir == 0) {
 		*delai_tir = 30;
 		
	}
	
	
	baseBg(renderer,values->score,values->duree,1);
	
	SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
    SDL_RenderFillRect(renderer, player_rect);
    
    drawFoes(nb_foes,foes,renderer);
	
	if (*delai_tir != 0){
		(*delai_tir)--;
	}
    return 1;
}

void main_loop_game_5(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer){  
	int* speed = malloc(sizeof(int));
	int* delai_tir = malloc(sizeof(int));
	int* nb_foes = malloc(sizeof(int));
	FoeStruct* foes = malloc(sizeof(FoeStruct)*NB_FOE_LINE*NB_FOE_COLUMN);
	*delai_tir = 0;
	(*speed) = SPEED;
	for (int i = 0; i < NB_FOE_LINE * NB_FOE_COLUMN ; i++){
		FoeStruct f;
		SDL_Rect t = {((WINDOW_WIDTH-NB_FOE_COLUMN*WIDTH_RECT)/2)+WIDTH_RECT*(i%NB_FOE_COLUMN),HEIGHT_RECT*(i/NB_FOE_COLUMN),WIDTH_RECT-2,HEIGHT_RECT-2}; // Ajouter à l'abscisse une constate dépendant du nombre de colonnes
		f.r = t;
		f.position = i;
		foes[i] = f;
	}
	*nb_foes = NB_FOE_LINE * NB_FOE_COLUMN;
 	SDL_Rect *player_rect = malloc(sizeof(SDL_Rect));
 	player_rect->x = (WINDOW_WIDTH/2)-(WIDTH_RECT/2);
 	player_rect->y = ORD_RECT;
 	player_rect->w = WIDTH_RECT;
 	player_rect->h = HEIGHT_RECT;
 	
 	int play = 1;
	while (play){
		play = play_game_5(game_event,renderer,values,player_rect,speed,delai_tir,foes,nb_foes);
		SDL_RenderPresent(renderer);
		SDL_Delay(REFRESH); 
    		
    	// *speed = *speed + (*speed / INITIAL_SPEED ); // Changer la fréquence d'apparition de cette ligne 

    }
    free(delai_tir);
   	free(speed);
    free(player_rect);
    free(foes);
    free(nb_foes);
	printf("Votre score est de %d !\n", values->score);
}
