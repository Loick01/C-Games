#include "game1.h"
#include "game2.h"
#include "game3.h"

int main(/*int argc, char *argv[]*/){
	srand(time(NULL));

	initialisation(); // Initialize colors, window and renderer
    st = EXIT_SUCCESS;    
    int choix = main_menu();
    void* values;
    SDL_Event game_event;
    
    
	// Faire un switch
    if (choix == 1){
    	values = init_game_1();
    	main_loop_game_1(game_event,(Values_game_1*)values,renderer);
    }else if (choix == 2){
    	values = init_game_2();
    	main_loop_game_2(game_event,(Values_game_2*)values,renderer);
    }else if (choix == 3){
    	values = init_game_3();
    	main_loop_game_3(game_event,(Values_game_3*)values,renderer);
    }
    
    free(values);
    free(colors);
	return clean_quit();
}




