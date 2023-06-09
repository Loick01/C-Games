#include "game1.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "game5.h"

int main(/*int argc, char *argv[]*/){
	srand(time(NULL));

	initialisation(); // Initialize colors, window and renderer
    st = EXIT_SUCCESS;    
    int choix = main_menu();
    void* values;
    SDL_Event game_event;
    
    
	switch(choix) {
        case 1:
            values = init_game_1();
    		main_loop_game_1(game_event,(Values_game_1*)values,renderer);
            break;
        case 2:
            values = init_game_simple();
    		main_loop_game_2(game_event,(Values_game_simple*)values,renderer);
            break;
        case 3:
           	values = init_game_3();
    		main_loop_game_3(game_event,(Values_game_3*)values,renderer);
            break;
        case 4:
        	values = init_game_simple();
    		main_loop_game_4(game_event,(Values_game_simple*)values,renderer);
    		break;
    	case 5:
    		values = init_game_5();
    		main_loop_game_5(game_event,(Values_game_5*)values,renderer);
    		break;
    }
    		

	if(choix != 0){
		free(values);
	}
    free(colors);
	return clean_quit();
}




