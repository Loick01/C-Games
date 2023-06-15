#include "game4.h"

int play_game_4(SDL_Event game_event,SDL_Renderer *renderer,SDL_Rect *player_rect, SDL_Rect to_dodge,int *nb_frame,int* speed){
	while (SDL_PollEvent(&game_event)){
		if(game_event.type == SDL_QUIT){
			return 2;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL); 
	if (state[SDL_SCANCODE_W] && player_rect->y >= 0) {
 		player_rect->y -= *speed;
	}
	if (state[SDL_SCANCODE_D] && player_rect->x + WIDTH_PLAYER <= WINDOW_WIDTH) {
 		player_rect->x += *speed;
	}
	if (state[SDL_SCANCODE_S] && player_rect->y + HEIGHT_PLAYER <= WINDOW_HEIGHT) {
 		player_rect->y += *speed;
	}
	if (state[SDL_SCANCODE_A] && player_rect->x >= 0) {
 		player_rect->x -= *speed;
	}
	
	actualiserWindow(renderer);
	
	if (*nb_frame >= 2*BASE_FRAME - (*speed * 2) && *nb_frame < 4*BASE_FRAME - (*speed * 2)){
		SDL_SetRenderDrawColor(renderer, colors[BUTTON1_COLOR].r, colors[BUTTON1_COLOR].g, 
										colors[BUTTON1_COLOR].b, colors[BUTTON1_COLOR].a);
		SDL_RenderFillRect(renderer, &to_dodge);
	}else if (*nb_frame >= 4*BASE_FRAME - (*speed * 2)){
		SDL_SetRenderDrawColor(renderer, colors[RED_COLOR].r, colors[RED_COLOR].g, colors[RED_COLOR].b, colors[RED_COLOR].a);
		SDL_RenderFillRect(renderer, &to_dodge);
		if (SDL_HasIntersection(player_rect,&to_dodge)){
			return 2;
		}
    }
    
    if (*nb_frame == 5*BASE_FRAME - (*speed * 2)){
    	*nb_frame = 0;
    	return 0;
    }else{
    	(*nb_frame)++;
    }
    
    SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
    SDL_RenderFillRect(renderer, player_rect);
    return 1;
}

void main_loop_game_4(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer){  
	int* speed = malloc(sizeof(int));
	(*speed) = INITIAL_SPEED;
 	SDL_Rect *player_rect = malloc(sizeof(SDL_Rect));
 	player_rect->x = (WINDOW_WIDTH/2)-(WIDTH_PLAYER/2);
 	player_rect->y = (WINDOW_HEIGHT/2)-(HEIGHT_PLAYER/2);
 	player_rect->w = WIDTH_PLAYER;
 	player_rect->h = HEIGHT_PLAYER;
 	
 	int rect_x[NB_RECT_DODGE] = {0,0,0,WINDOW_WIDTH/2,AWAY_FROM_WINDOW};
 	int rect_y[NB_RECT_DODGE] = {0,WINDOW_HEIGHT/2,0,0,AWAY_FROM_WINDOW};
	int rect_width[NB_RECT_DODGE] = {WINDOW_WIDTH,WINDOW_WIDTH,WINDOW_WIDTH/2,WINDOW_WIDTH/2,WINDOW_WIDTH-2*AWAY_FROM_WINDOW};
 	int rect_height[NB_RECT_DODGE] = {WINDOW_HEIGHT/2,WINDOW_HEIGHT/2,WINDOW_HEIGHT,WINDOW_HEIGHT,WINDOW_HEIGHT-2*AWAY_FROM_WINDOW};
 	
 	SDL_Rect *rect_dodge = malloc(sizeof(SDL_Rect)*NB_RECT_DODGE);
 	for (int i = 0 ; i < NB_RECT_DODGE ; i++){
 		SDL_Rect r = {rect_x[i],rect_y[i],rect_width[i],rect_height[i]};
 		rect_dodge[i] = r;
 	}
 	
 	int b = 1;
	while (b){
		int play = 1;	
		int c = rand() % NB_RECT_DODGE;
		SDL_Rect to_dodge = rect_dodge[c];
		int *nb_frame = malloc(sizeof(int));
		*nb_frame = 0;
    	while(play==1){
    		play = play_game_4(game_event,renderer,player_rect,to_dodge,nb_frame,speed);
		    SDL_RenderPresent(renderer);
		    SDL_Delay(REFRESH); 
    	}	
    	if (play != 2){
    		values->score++;
    	}
    	*speed = *speed + (*speed / INITIAL_SPEED );
    	free(nb_frame);
    	b = (play != 2 ? 1 : 0) ;
    }
    
    free(speed);
    free(player_rect);
    free(rect_dodge);
	printf("Votre score est de %d !\n", values->score);
}
