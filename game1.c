#include "game1.h"

Values_game_1* init_game_1(){
	Values_game_1* values = malloc(sizeof(Values_game_1));
	values->score = 0;
	values->direction = 1;
	values->player_x = SPACE_X;
	values->duree = TIME;
	values->wrong = 0;
	return values;
}


int play_game_1(SDL_Event game_event,Values_game_1* values,SDL_Renderer *renderer,int cible_length,int cible_x,int vitesse){
	if (SDL_PollEvent(&game_event)){
		if(game_event.type == SDL_QUIT){
			values->duree = 0;
			return 0;
		}
		else if (game_event.type == SDL_KEYDOWN && values->wrong == 0){
			if(game_event.key.keysym.scancode == SDL_SCANCODE_SPACE){
            	if ( (values->player_x >= cible_x && cible_x + cible_length >= values->player_x) 
            		||
            		(values->player_x + PLAYER_WIDTH >= cible_x && cible_x + cible_length >= values->player_x + PLAYER_WIDTH)){
            		values->score++;
            		return 0;
            	} else {
            		values->wrong = 50;
            	}		
			}
		}
	}

	if (values->wrong > 0){
		values->wrong--;
	}	
    baseBg(renderer,values->score,values->duree,0);
    dessiner_rect(colors[WHITE_COLOR], SPACE_X, SPACE_Y,SPACE_WIDTH,SPACE_HEIGHT);
   	dessiner_rect(colors[GREEN_COLOR],cible_x,SPACE_Y,cible_length,SPACE_HEIGHT); 
    dessiner_rect(values->wrong == 0 ? colors[BLACK_COLOR] : colors[RED_COLOR] ,values->player_x,(WINDOW_HEIGHT / 2) - (PLAYER_HEIGHT / 2),PLAYER_WIDTH,PLAYER_HEIGHT);	
    values->player_x += (vitesse * values->direction);
    if (values->player_x <= SPACE_X){
    	values->direction = 1;
    }else if (values->player_x + PLAYER_WIDTH >= SPACE_X + SPACE_WIDTH){
    	values->direction = -1;
    }
    return 1;
}


void main_loop_game_1(SDL_Event game_event,Values_game_1* values,SDL_Renderer *renderer){
	while (values->duree > 0){
    	int cible_length = MIN_SIZE_CIBLE + (rand() % MAX_SIZE_CIBLE);
    	int cible_x = SPACE_X + (rand() % (SPACE_WIDTH - cible_length));
		int vitesse = MIN_SPEED + (rand() % MAX_SPEED);
		
		int play = 1;		
    	while(play){
    		play = play_game_1(game_event,values,renderer,cible_length,cible_x,vitesse);
		    SDL_RenderPresent(renderer);
		    values->duree -= REFRESH;
		    if (values->duree < 0){
		    	break;
		    }
		    SDL_Delay(REFRESH); 
    	}	
    }
     printf("Votre score est de %d !\n", values->score);
}


