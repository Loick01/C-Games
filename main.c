#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MIN_SIZE_CIBLE 50
#define MAX_SIZE_CIBLE 200

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 200

#define SPACE_WIDTH WINDOW_WIDTH - (2 * SPACE_X)
#define SPACE_HEIGHT 40
#define SPACE_X 50
#define SPACE_Y 280

#define MIN_SPEED 10
#define MAX_SPEED 15

#define TIME 30000
#define REFRESH 20

SDL_Color bgc = {2, 81, 112, 255};
SDL_Color cible_color = {5, 99, 35, 255};
SDL_Color bande_color = {255,255,255,255};
SDL_Color player_color = {0,0,0,255};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int st = EXIT_FAILURE;

int clean_quit(SDL_Renderer *renderer,SDL_Window *window){
    if(renderer != NULL){
        SDL_DestroyRenderer(renderer);
    }
    if(window != NULL){
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return st;
}

void dessiner_rect(SDL_Color c, int x, int y, int w, int h){
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &rect);
}

void actualiserWindow(SDL_Renderer *renderer,SDL_Window *window){
	SDL_SetRenderDrawColor(renderer, bgc.r, bgc.g, bgc.b, bgc.a);
    SDL_RenderClear(renderer);
}


int main(int argc, char *argv[]){
	srand(time(NULL));
	
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Impossible d'initialiser la SDL : %s", SDL_GetError());
        clean_quit(renderer,window);
    }

    window = SDL_CreateWindow("C GAMES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        fprintf(stderr, "Impossible de créer la fenêtre : %s", SDL_GetError());
        clean_quit(renderer,window);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr, "Impossible de créer le rendu pour la fenêtre : %s", SDL_GetError());
        clean_quit(renderer,window);
    }

    st = EXIT_SUCCESS;
            
    SDL_Event event;   
    int score = 0;
    int direction = 1; // 1 vers la droite, -1 vers la gauche
    int player_x = 50;
    int duree = TIME;
    
    while (duree > 0){
    	int cible_length = MIN_SIZE_CIBLE + (rand() % MAX_SIZE_CIBLE);
    	int cible_x = SPACE_X + (rand() % ((SPACE_WIDTH + SPACE_X) - cible_length));
		int vitesse = MIN_SPEED + (rand() % MAX_SPEED);
		
    	while(1){
    		if (SDL_PollEvent(&event)){
				if(event.type == SDL_QUIT){
					printf("Votre score est de %d !\n", score);
				   	return clean_quit(renderer,window);
				}
				else if (event.type == SDL_KEYDOWN){
					if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
            			if ( player_x >= cible_x && cible_x + cible_length >= player_x 
            				||
            				 player_x + PLAYER_WIDTH >= cible_x && cible_x + cible_length >= player_x + PLAYER_WIDTH){
            				score++;
            				break;
            			}		
					}
				}
			}
    	
        	actualiserWindow(renderer,window);
        	dessiner_rect(bande_color, SPACE_X, SPACE_Y,SPACE_WIDTH,SPACE_HEIGHT);
    		dessiner_rect(cible_color,cible_x,SPACE_Y,cible_length,SPACE_HEIGHT); 
    		dessiner_rect(player_color,player_x,(WINDOW_HEIGHT / 2) - (PLAYER_HEIGHT / 2),PLAYER_WIDTH,PLAYER_HEIGHT);
    		
    		player_x += (vitesse * direction);
    		if (player_x <= SPACE_X){
    			direction = 1;
    		}else if (player_x + PLAYER_WIDTH >= SPACE_X + SPACE_WIDTH){
    			direction = -1;
    		}
    		
		    SDL_RenderPresent(renderer);
		    duree -= REFRESH;
		    SDL_Delay(REFRESH); 
    	}
    	
    }
    
    printf("Votre score est de %d !\n", score);
	return clean_quit(renderer,window);

}
