#include "game3.h"

int play_game_3(SDL_Event game_event,Values_game_simple* values,int lettre){
	if (SDL_PollEvent(&game_event)){ // Peut être un while plutot (à voir)
		if(game_event.type == SDL_QUIT){
			values->duree = 0;
			return 0;
		}
		else if (game_event.type == SDL_KEYDOWN){
			SDL_Keycode keycode = game_event.key.keysym.sym;
            const char* keyName = SDL_GetKeyName(keycode);
            if (*keyName == lettre){
		        values->score++;
		        return 0;
		    }
		}
	}
    
    return 1;
}

void main_loop_game_3(SDL_Event game_event,Values_game_simple* values,SDL_Renderer *renderer){
	TTF_Font* font_lettre = TTF_OpenFont("roboto-bold.ttf", FONT_LETTER_SIZE);
	char* cible = malloc(2*sizeof(char));	
	char* next = malloc((NUMBER_FOLLOWING_LETTER+1)*sizeof(char));
	cible[1] = '\0';
	next[NUMBER_FOLLOWING_LETTER] = '\0';
	for (int i=0 ; i< NUMBER_FOLLOWING_LETTER ; i++){
		next[i] = 65 + (rand()%26);
	}
    SDL_Rect lettre_rect = {50,(WINDOW_HEIGHT/2)-(HEIGHT_LETTER/2),WIDTH_LETTER,HEIGHT_LETTER};
    SDL_Rect next_rect = {50+WIDTH_LETTER,(WINDOW_HEIGHT/2)-(HEIGHT_LETTER/2),NUMBER_FOLLOWING_LETTER*WIDTH_LETTER,HEIGHT_LETTER};
    SDL_Surface* surface_lettre;
    SDL_Texture* texture_lettre;
    SDL_Surface* next_surfaces_lettres;
    SDL_Texture* next_texture_lettres;
    
	while (values->duree > 0){
		cible[0] = next[0];
		int new_lettre = 65 + (rand()%26);
		for (int i=0 ; i< NUMBER_FOLLOWING_LETTER-1 ; i++){
			next[i] = next[i+1];
		}
		next[NUMBER_FOLLOWING_LETTER-1] = (char) new_lettre;
		
		actualiserWindow(renderer);
		
		surface_lettre = TTF_RenderText_Solid(font_lettre, cible, colors[WHITE_COLOR]); 
		texture_lettre = SDL_CreateTextureFromSurface(renderer, surface_lettre);
		SDL_RenderCopy(renderer, texture_lettre, NULL, &lettre_rect);
		
		next_surfaces_lettres = TTF_RenderText_Solid(font_lettre, next, colors[TRANSPARENT_WHITE_COLOR]); 
		next_texture_lettres = SDL_CreateTextureFromSurface(renderer, next_surfaces_lettres);
		SDL_RenderCopy(renderer, next_texture_lettres, NULL, &next_rect);
		
		SDL_RenderPresent(renderer);
	
		int play = 1;	
    	while(play){
    		
    		play = play_game_3(game_event,values,(int)cible[0]);
		    values->duree -= REFRESH;
		    if (values->duree < 0){
		    	break;
		    }
		    SDL_Delay(REFRESH); 
    	}	
    	SDL_DestroyTexture(texture_lettre);
		SDL_FreeSurface(surface_lettre);
		SDL_DestroyTexture(next_texture_lettres);
		SDL_FreeSurface(next_surfaces_lettres);
    }
    
	TTF_CloseFont(font_lettre);
	TTF_Quit();
	
	free(cible);
	free(next);
	printf("Votre score est de %d !\n", values->score);
}


