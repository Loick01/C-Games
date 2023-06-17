#include "game3.h"

Values_game_3* init_game_3(){
	Values_game_3* values = malloc(sizeof(Values_game_3));
	values->score = 0;
	values->duree = TIME;
	values->font_lettre = TTF_OpenFont("roboto-bold.ttf", FONT_LETTER_SIZE);
	SDL_Rect lr = {50,(WINDOW_HEIGHT/2)-(HEIGHT_LETTER/2),WIDTH_LETTER,HEIGHT_LETTER};
	values->lettre_rect = lr;
	SDL_Rect nr = {50+WIDTH_LETTER,(WINDOW_HEIGHT/2)-(HEIGHT_LETTER/2),NUMBER_FOLLOWING_LETTER*WIDTH_LETTER,HEIGHT_LETTER};
    values->next_rect = nr;
	return values;
}

int play_game_3(SDL_Event game_event,Values_game_3* values,char* cible,char* next){
	while (SDL_PollEvent(&game_event)){ 
		if(game_event.type == SDL_QUIT){
			values->duree = 0;
			return 0;
		}
		else if (game_event.type == SDL_KEYDOWN){
			SDL_Keycode keycode = game_event.key.keysym.sym;
            const char* keyName = SDL_GetKeyName(keycode);
            if (*keyName == (int)cible[0]){
		        values->score++;
		        return 0;
		    }
		}
	}
	
	baseBg(renderer,values->score,values->duree,0);
		
	values->surface_lettre = TTF_RenderText_Solid(values->font_lettre, cible, colors[WHITE_COLOR]); 
	values->texture_lettre = SDL_CreateTextureFromSurface(renderer, values->surface_lettre);
	SDL_RenderCopy(renderer, values->texture_lettre, NULL, &(values->lettre_rect));
		
	values->next_surfaces_lettres = TTF_RenderText_Solid(values->font_lettre, next, colors[TRANSPARENT_WHITE_COLOR]); 
	values->next_texture_lettres = SDL_CreateTextureFromSurface(renderer, values->next_surfaces_lettres);
	SDL_RenderCopy(renderer, values->next_texture_lettres, NULL, &(values->next_rect));
    
    return 1;
}

void main_loop_game_3(SDL_Event game_event,Values_game_3* values,SDL_Renderer *renderer){
	char* cible = malloc(2*sizeof(char));	// A revoir
	char* next = malloc((NUMBER_FOLLOWING_LETTER+1)*sizeof(char));
	cible[1] = '\0';
	next[NUMBER_FOLLOWING_LETTER] = '\0';
	for (int i=0 ; i< NUMBER_FOLLOWING_LETTER ; i++){
		next[i] = 65 + (rand()%26);
	}
    
	while (values->duree > 0){
		cible[0] = next[0];
		int new_lettre = 65 + (rand()%26);
		for (int i=0 ; i< NUMBER_FOLLOWING_LETTER-1 ; i++){
			next[i] = next[i+1];
		}
		next[NUMBER_FOLLOWING_LETTER-1] = (char) new_lettre;
		
		int play = 1;	
    	while(play){
    		
    		play = play_game_3(game_event,values,cible,next);
    		SDL_RenderPresent(renderer);
		    values->duree -= REFRESH;
		    if (values->duree < 0){
		    	break;
		    }
		    SDL_Delay(REFRESH); 
    	}	
    }
    
    SDL_DestroyTexture(values->texture_lettre);
	SDL_FreeSurface(values->surface_lettre);
	SDL_DestroyTexture(values->next_texture_lettres);
	SDL_FreeSurface(values->next_surfaces_lettres);
	TTF_CloseFont(values->font_lettre);
	
	free(cible);
	free(next);
	printf("Votre score est de %d !\n", values->score);
}


