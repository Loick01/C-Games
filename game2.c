#include "game2.h"


int play_game_2(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer,SDL_Rect cible,SDL_Point point,int* x,int* y){
	while(SDL_PollEvent(&game_event)){
		if(game_event.type == SDL_QUIT){
			values->duree = 0;
			return 0;
		}
		else if (game_event.type == SDL_MOUSEBUTTONDOWN){
			if(game_event.button.button == SDL_BUTTON_LEFT){
            	SDL_GetMouseState(x,y);
				point.x = *x;
				point.y = *y;
				if (SDL_PointInRect(&point,&cible)){
					values->score++;
            		return 0;
				}
			}
		}		
	}
	
	
	baseBg(renderer,values->score,values->duree,0);
	SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
    SDL_RenderFillRect(renderer, &cible);
    
    return 1;
}


void main_loop_game_2(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer){
	SDL_Point point;
	int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));	
    SDL_Rect cible;
	while (values->duree > 0){
		int square_size = MIN_SQUARE_SIZE;
		int square_x = PLAY_AREA_LIMIT + (rand() % (WINDOW_WIDTH - 2*PLAY_AREA_LIMIT - square_size));
		int square_y = PLAY_AREA_LIMIT + (rand() % (WINDOW_HEIGHT - 2*PLAY_AREA_LIMIT - square_size));;
		int play = 1;	
    	while(play){
    		if (square_size < MAX_SQUARE_SIZE){
				square_size += 2 * AUGMENTATION;
				square_x -= AUGMENTATION;
				square_y -= AUGMENTATION;
	  			cible.w = square_size;
				cible.h = square_size;
				cible.x = square_x;
				cible.y = square_y;
			}
    		play = play_game_2(game_event,values,renderer,cible,point,x,y);
		    SDL_RenderPresent(renderer);
		    values->duree -= REFRESH;
		    if (values->duree < 0){
		    	break;
		    }
		    SDL_Delay(REFRESH); 
    	}	
    }
    free(x);
    free(y);
    printf("Votre score est de %d !\n", values->score);
}
