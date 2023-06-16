#include "game4.h"

int play_game_4(SDL_Event game_event,SDL_Renderer *renderer,Values_game_simple* values,SDL_Rect *player_rect,int* speed,int* nb_rect_dodge,Rect_Struct** rect_dodge){
	while (SDL_PollEvent(&game_event)){
		if(game_event.type == SDL_QUIT){
			return 0;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL); 
	if (state[SDL_SCANCODE_W] && player_rect->y >= 0) {
 		player_rect->y -= *speed;
	}
	if (state[SDL_SCANCODE_D] && player_rect->x + WIDTH_RECT <= WINDOW_WIDTH) {
 		player_rect->x += *speed;
	}
	if (state[SDL_SCANCODE_S] && player_rect->y + HEIGHT_RECT <= WINDOW_HEIGHT) {
 		player_rect->y += *speed;
	}
	if (state[SDL_SCANCODE_A] && player_rect->x >= 0) {
 		player_rect->x -= *speed;
	}
	
	if (*nb_rect_dodge < NB_RECT_DODGE){
		int c = rand() % ((*nb_rect_dodge + 1));
		if (c==0){
			Rect_Struct *new_rect = malloc(sizeof(Rect_Struct));
			int rect_x ;
			int rect_y ;
			
			int var = rand() % 4;
			if (var == 0){
				new_rect->dir_x = 1;
				new_rect->dir_y = 0;
				rect_x = 0 - WIDTH_RECT;
				rect_y = rand() % (WINDOW_HEIGHT - HEIGHT_RECT);
			}else if (var == 1){
				new_rect->dir_x = -1;
				new_rect->dir_y = 0;
				rect_x = WINDOW_WIDTH;
				rect_y = rand() % (WINDOW_HEIGHT - HEIGHT_RECT);
			}
			else if (var == 2){
				new_rect->dir_x = 0;
				new_rect->dir_y = 1;
				rect_x = rand() % (WINDOW_WIDTH - WIDTH_RECT);
				rect_y = 0 - HEIGHT_RECT;
			}
			else if (var == 3){
				new_rect->dir_x = 0;
				new_rect->dir_y = -1;
				rect_x = rand() % (WINDOW_WIDTH - WIDTH_RECT);
				rect_y = WINDOW_HEIGHT;
			}
			
			SDL_Rect temp = {rect_x ,rect_y,WIDTH_RECT,HEIGHT_RECT};
			new_rect->r = temp;
			new_rect->lifetime = WINDOW_WIDTH / *speed + 5;
			rect_dodge[*nb_rect_dodge] = new_rect;
			(*nb_rect_dodge)++;
		}
	}
	
	baseBg(renderer,values->score,values->duree,1);
	
	SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
    SDL_RenderFillRect(renderer, player_rect);
    
	SDL_SetRenderDrawColor(renderer, colors[RED_COLOR].r, colors[RED_COLOR].g, colors[RED_COLOR].b, colors[RED_COLOR].a);
	
	for (int i = 0 ; i < *nb_rect_dodge ; i++){
    	SDL_RenderFillRect(renderer,&((rect_dodge[i]->r)));
   
    	if (SDL_HasIntersection(player_rect,&((rect_dodge[i]->r)))){
    		return 0;
    	}
    	
    	(rect_dodge[i])->lifetime--;
    	(rect_dodge[i])->r.x += *speed * (rect_dodge[i])->dir_x; // Same speed than player
    	(rect_dodge[i])->r.y += *speed * (rect_dodge[i])->dir_y; // Same speed than player
    	
    	
    	if ((rect_dodge[i])->lifetime == 0){
    		values->score++;
    		free(rect_dodge[i]);
    		rect_dodge[i] = rect_dodge[(*nb_rect_dodge)-1];
    		(*nb_rect_dodge)--;
    	}
    	
    	
	}
	
	
    return 1;
}

void main_loop_game_4(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer){  
	int* speed = malloc(sizeof(int));
	(*speed) = INITIAL_SPEED;
 	SDL_Rect *player_rect = malloc(sizeof(SDL_Rect));
 	player_rect->x = (WINDOW_WIDTH/2)-(WIDTH_RECT/2);
 	player_rect->y = (WINDOW_HEIGHT/2)-(HEIGHT_RECT/2);
 	player_rect->w = WIDTH_RECT;
 	player_rect->h = HEIGHT_RECT;
 	
 	Rect_Struct** rect_dodge = malloc(sizeof(Rect_Struct*)*NB_RECT_DODGE);
 	int* nb_rect_dodge = malloc(sizeof(int));
 	*nb_rect_dodge = 0;
 	
 	int play = 1;
	while (play){
		play = play_game_4(game_event,renderer,values,player_rect,speed,nb_rect_dodge,rect_dodge);
		SDL_RenderPresent(renderer);
		SDL_Delay(REFRESH); 
    		
    	// *speed = *speed + (*speed / INITIAL_SPEED ); // Changer la fréquence d'apparition de cette ligne 

    }
   	free(speed);
    free(player_rect);
    for (int i = 0; i < *nb_rect_dodge ; i++){ // Pour être sûr on pourrait carrément tout le tableau (selon NB_RECT_DODGE qui vaut ici 50)
    	free(rect_dodge[i]); // rect_dodge is pointer to an array of pointer
    }
    free(rect_dodge);
    free(nb_rect_dodge);
	printf("Votre score est de %d !\n", values->score);
}
