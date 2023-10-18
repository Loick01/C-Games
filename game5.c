#include "game5.h"

Values_game_5* init_game_5(){
	Values_game_5* values = malloc(sizeof(Values_game_5));

	values->score = 0;
	values->duree = TIME;
	values->speed = SPEED;
	values->delai_tir = 0;
	values->foes = malloc(sizeof(FoeStruct*)*NB_FOE_LINE*NB_FOE_COLUMN);
	values->tirs = malloc(sizeof(SDL_Rect*)*20); 
	values->nb_tirs = 0;
	values->direct_foes = malloc(sizeof(FoeStruct*)*NB_FOE_COLUMN);
	for (int i = 0; i < NB_FOE_LINE * NB_FOE_COLUMN ; i++){
		FoeStruct* f = malloc(sizeof(FoeStruct));
		SDL_Rect t = {((WINDOW_WIDTH-NB_FOE_COLUMN*WIDTH_RECT)/2)+WIDTH_RECT*(i%NB_FOE_COLUMN),HEIGHT_RECT*(i/NB_FOE_COLUMN),WIDTH_RECT-2,HEIGHT_RECT-2}; 
		f->r = t;
		f->position = i;
		(values->foes)[i] = f;
	}
	for (int i = NB_FOE_LINE * NB_FOE_COLUMN - NB_FOE_COLUMN ; i < NB_FOE_LINE * NB_FOE_COLUMN ; i++){
		int j = i % (NB_FOE_LINE * NB_FOE_COLUMN - NB_FOE_COLUMN);
		(values->direct_foes)[j] = (values->foes)[i];
	}
	
 	values->player_rect = malloc(sizeof(SDL_Rect));
 	values->player_rect->x = (WINDOW_WIDTH/2)-(WIDTH_RECT/2);
 	values->player_rect->y = ORD_RECT;
 	values->player_rect->w = WIDTH_RECT;
 	values->player_rect->h = HEIGHT_RECT;
 	
	return values;
}


void drawFoes(FoeStruct** foes,SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, colors[RED_COLOR].r, colors[RED_COLOR].g, colors[RED_COLOR].b, colors[RED_COLOR].a);
	for (int i = 0; i < NB_FOE_LINE*NB_FOE_COLUMN ; i++){
		if (foes[i] != NULL){
			SDL_RenderFillRect(renderer, &((foes[i])->r));
		}
	}
}

void deleteTir(Values_game_5* values,int i){
	free((values->tirs)[i]);
    (values->tirs)[i] = (values->tirs)[values->nb_tirs - 1];
    (values->nb_tirs)--;
}


void deleteFoe(Values_game_5* values,int col){
	int n = ((values->direct_foes)[col])->position;
	free((values->direct_foes)[col]); // also free in values->foes because it's the same pointer
	if (n-NB_FOE_COLUMN >= 0){ 
		(values->direct_foes)[col] = values->foes[n-NB_FOE_COLUMN];
	}else{
		(values->direct_foes)[col] = NULL;
	}
	values->foes[n] = NULL;
}


int play_game_5(SDL_Event game_event,SDL_Renderer *renderer,Values_game_5* values){
	while (SDL_PollEvent(&game_event)){
		if(game_event.type == SDL_QUIT){
			return 0;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL); 
	if (state[SDL_SCANCODE_D] && values->player_rect->x + WIDTH_RECT <= WINDOW_WIDTH) {
 		values->player_rect->x += values->speed;
	}
	if (state[SDL_SCANCODE_A] && values->player_rect->x >= 0) {
 		values->player_rect->x -= values->speed;
	}
	if (state[SDL_SCANCODE_SPACE] && values->delai_tir == 0) {
 		values->delai_tir = 10;
 		SDL_Rect *r = malloc(sizeof(SDL_Rect));
 		r->x = values->player_rect->x + WIDTH_RECT/2;
 		r->y = ORD_RECT;
 		r->w = WIDTH_TIR;
 		r->h = HEIGHT_TIR;
 		
 		(values->tirs)[values->nb_tirs] = r;
 		values->nb_tirs++;
	}
	
	
	baseBg(renderer,values->score,values->duree,1);
	
	SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
    SDL_RenderFillRect(renderer, values->player_rect);
    
    drawFoes(values->foes,renderer);
    
    SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
    for (int i = 0; i < values->nb_tirs; i++){
    	SDL_RenderFillRect(renderer, (values->tirs)[i]);
    	((values->tirs)[i])->y -= SPEED_TIR;
    	
    	if (((values->tirs)[i])->y < HEIGHT_TIR*-1){
    		deleteTir(values,i);
    	}else{
    		int col = ((((values->tirs)[i])->x) - ((WINDOW_WIDTH-NB_FOE_COLUMN*WIDTH_RECT)/2)) / WIDTH_RECT; 
    		if (col >= 0 && col < NB_FOE_COLUMN && SDL_HasIntersection((values->tirs)[i],&(((values->direct_foes)[col])->r))){
    			(values->score)++;
    			deleteTir(values,i);
    			deleteFoe(values,col);
    		}
    	}
    }
	
	if (values->delai_tir != 0){
		(values->delai_tir)--;
	}
    return 1;
}

void main_loop_game_5(SDL_Event game_event,Values_game_5* values,SDL_Renderer *renderer){  
 	int play = 1;
	while (play){
		play = play_game_5(game_event,renderer,values);
		SDL_RenderPresent(renderer);
		SDL_Delay(REFRESH); 
    		
    	// *speed = *speed + (*speed / INITIAL_SPEED ); // Changer la fréquence d'apparition de cette ligne 

    }
    
    for (int i = 0; i < values->nb_tirs ; i++){
    	free((values->tirs)[i]);
    }
    free(values->tirs);
    for (int i = 0; i < NB_FOE_LINE*NB_FOE_COLUMN ; i++){
    	FoeStruct *t = (values->foes)[i];
    	if (t != NULL){
    		free((values->foes)[i]);
    	}
    }
    free(values->foes);
    free(values->player_rect);
	printf("Votre score est de %d !\n", values->score);
}
