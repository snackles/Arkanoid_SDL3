#include "../include/arkanoid.hpp"

int main(){

	GameData game;

	initGame(game);
	game.last_time = SDL_GetTicks();
	while (game.is_running) {			
		Uint32 current_time = SDL_GetTicks();
		game.delta_time = (current_time - game.last_time) / 1000.0f;
		game.last_time = current_time;;
		processEvent(game);
		renderGame(game);
	}

	destroyObjects(game);
	SDL_Quit();
	
	return 0;
}
