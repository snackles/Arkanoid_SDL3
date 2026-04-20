#include "../include/arkanoid.hpp"

int main(){

	GameData game;
	bool done = false;

	initGame(game);

	while (!done) {
		renderGame(game);	
        SDL_Event event;		
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
	}

	destroyObjects(game);
	SDL_Quit();
	
	return 0;
}
