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

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 150
#define BUTTON_X 250

#define TIME 30000
#define REFRESH 20


SDL_Color bgc = {2, 81, 112, 255};
SDL_Color cible_color = {5, 99, 35, 255};
SDL_Color bande_color = {255,255,255,255};
SDL_Color player_color = {0,0,0,255};
SDL_Color wrong_color = {240,20,20,255};
SDL_Color button1_color = {230, 146, 21, 255};
SDL_Color button2_color = {166, 8, 16, 255};

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

typedef struct{
	int score;
    int direction; // 1 vers la droite, -1 vers la gauche
    int player_x;
    int duree;
    int wrong;
} Values_game_1;

Values_game_1* init_game_1(){
	Values_game_1* values = malloc(sizeof(Values_game_1));
	(*values).score = 0;
	(*values).direction = 1;
	(*values).player_x = SPACE_X;
	(*values).duree = TIME;
	(*values).wrong = 0;
	return values;
}

int play_game_1(Values_game_1* values,SDL_Renderer *renderer,SDL_Window *window,int cible_length,int cible_x,int vitesse){
	SDL_Event game_1_event; 
	if (SDL_PollEvent(&game_1_event)){
		if(game_1_event.type == SDL_QUIT){
			values->duree = 0;
			return 0;
		}
		else if (game_1_event.type == SDL_KEYDOWN && values->wrong == 0){
			if(game_1_event.key.keysym.scancode == SDL_SCANCODE_SPACE){
            	if ( values->player_x >= cible_x && cible_x + cible_length >= values->player_x 
            		||
            		values->player_x + PLAYER_WIDTH >= cible_x && cible_x + cible_length >= values->player_x + PLAYER_WIDTH){
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
    actualiserWindow(renderer,window);
    dessiner_rect(bande_color, SPACE_X, SPACE_Y,SPACE_WIDTH,SPACE_HEIGHT);
   	dessiner_rect(cible_color,cible_x,SPACE_Y,cible_length,SPACE_HEIGHT); 
    dessiner_rect(values->wrong == 0 ? player_color : wrong_color ,values->player_x,(WINDOW_HEIGHT / 2) - (PLAYER_HEIGHT / 2),PLAYER_WIDTH,PLAYER_HEIGHT);	
    values->player_x += (vitesse * values->direction);
    if (values->player_x <= SPACE_X){
    	values->direction = 1;
    }else if (values->player_x + PLAYER_WIDTH >= SPACE_X + SPACE_WIDTH){
    	values->direction = -1;
    }
    return 1;
}

int main_menu(){
	int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));
    SDL_Event menu_event;  
   	SDL_Point point;
   	
   	actualiserWindow(renderer,window);
   	SDL_SetRenderDrawColor(renderer, button1_color.r, button1_color.g, button1_color.b, button1_color.a);
    SDL_Rect button1 = {BUTTON_X,100,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button1);
    SDL_SetRenderDrawColor(renderer, button2_color.r, button2_color.g, button2_color.b, button2_color.a);
    SDL_Rect button2 = {BUTTON_X,350,BUTTON_WIDTH,BUTTON_HEIGHT};
    SDL_RenderFillRect(renderer, &button2);
    SDL_RenderPresent(renderer);
    
   	int choix = 0;
    while (choix == 0){
    	if (SDL_WaitEvent(&menu_event)){
			if(menu_event.type == SDL_QUIT){
				free(x);
				free(y);
				return clean_quit(renderer,window);
			}
			if(menu_event.type == SDL_MOUSEBUTTONDOWN){
				if(menu_event.button.button == SDL_BUTTON_LEFT){
					SDL_GetMouseState(x,y);
					point.x = *x;
					point.y = *y;
					if (SDL_PointInRect(&point,&button1)){
						choix = 1;
					}else if(SDL_PointInRect(&point,&button2)){
						choix = 2;
					}
				}
			}
		}
    }
    free(x);
    free(y);
    return choix;
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
    
    int choix = main_menu();
    
    
    Values_game_1* values;
    
    if (choix == 1){
    	values = init_game_1();
    }else if (choix == 2){
    	printf("Choix 2\n");
    	//Values_game_2* values = init_game_2();
    	return clean_quit(renderer,window);
    }
    
    while (values->duree > 0){
    	int cible_length = MIN_SIZE_CIBLE + (rand() % MAX_SIZE_CIBLE);
    	int cible_x = SPACE_X + (rand() % ((SPACE_WIDTH + SPACE_X) - cible_length));
		int vitesse = MIN_SPEED + (rand() % MAX_SPEED);
		
		int play = 1;		
    	while(play){
    		play = play_game_1(values,renderer,window,cible_length,cible_x,vitesse);
		    SDL_RenderPresent(renderer);
		    values->duree -= REFRESH;
		    SDL_Delay(REFRESH); 
    	}
    	
    }
    
    printf("Votre score est de %d !\n", values->score);
    free(values);
	return clean_quit(renderer,window);

}
