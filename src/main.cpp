#include "../include/arkanoid.hpp"

int main(){

	GameData game;

	initGame(game);
	game.last_time = SDL_GetTicks();
	while (game.is_running) {			
		processEvent(game);
		Uint32 current_time = SDL_GetTicks();
		game.delta_time = (current_time - game.last_time) / 1000.0f;
		game.last_time = current_time;

		renderGame(game);

		if (!game.is_paused && game.game_state == STATE_PLAYING) {
			updateGame(game, game.delta_time);
		}
             
		if (game.delta_time < FRAME_TIME) {
			SDL_Delay(static_cast<Uint32>((FRAME_TIME - game.delta_time) * 1000));
		}
	}

	destroyObjects(game);
	SDL_Quit();
	
	return 0;
}
