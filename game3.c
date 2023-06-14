#include "game3.h"

Values_game_3* init_game_3(){
	Values_game_3* values = malloc(sizeof(Values_game_3));
	(*values).score = 0;
	(*values).duree = TIME;
	return values;
}

int play_game_3(SDL_Event game_event,Values_game_3* values,int lettre){
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

void main_loop_game_3(SDL_Event game_event,Values_game_3* values,SDL_Renderer *renderer){
	TTF_Font* font_lettre = TTF_OpenFont("roboto-bold.ttf", FONT_LETTER_SIZE);
	char* cible = malloc(2*sizeof(char));	
	cible[1] = '\0';
    SDL_Rect lettre_rect = {(WINDOW_WIDTH/2)-(WIDTH_LETTER/2),(WINDOW_HEIGHT/2)-(HEIGHT_LETTER/2),WIDTH_LETTER,HEIGHT_LETTER};
    SDL_Surface* surface_lettre;
    SDL_Texture* texture_lettre;
    
	while (values->duree > 0){
		int lettre = 65 + (rand()%26);
		cible[0] = (char)lettre;
		actualiserWindow(renderer);
		SDL_SetRenderDrawColor(renderer, colors[WHITE_COLOR].r, colors[WHITE_COLOR].g, colors[WHITE_COLOR].b, colors[WHITE_COLOR].a);
		surface_lettre = TTF_RenderText_Solid(font_lettre, cible, colors[WHITE_COLOR]); 
		texture_lettre = SDL_CreateTextureFromSurface(renderer, surface_lettre);
		SDL_RenderCopy(renderer, texture_lettre, NULL, &lettre_rect);
		SDL_RenderPresent(renderer);
	
		int play = 1;	
    	while(play){
    		
    		play = play_game_3(game_event,values,lettre);
		    values->duree -= REFRESH;
		    if (values->duree < 0){
		    	break;
		    }
		    SDL_Delay(REFRESH); 
    	}	
    	SDL_DestroyTexture(texture_lettre);
		SDL_FreeSurface(surface_lettre);
    }
    
	TTF_CloseFont(font_lettre);
	TTF_Quit();
	
	free(cible);
	printf("Votre score est de %d !\n", values->score);
}


