#include "../include/arkanoid.hpp"
#include "../include/constants.hpp"

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

void processEvent(GameData &game){

    while (SDL_PollEvent(&game.event)) {
		
        switch (game.event.type) {
			
		case SDL_EVENT_QUIT:
			game.is_running = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			handleKeyPress(game, game.event.key.key);
			break;
		case SDL_EVENT_KEY_UP:
			handleKeyRelease(game, game.event.key.key);
			break;
		}
	}
	handleKeyboard(game);
}

void handleKeyPress(GameData& game, SDL_Keycode key) {
	
    if (game.event.key.repeat) {
		
        return;
    }
    switch (key) {
		
	case KEY_QUIT:
		game.is_running = false;
		break;
	case KEY_START:
		if (game.ball.state == 0){
			game.ball.state = 1;
			game.ball.direction.x = 0.5;
			game.ball.direction.y = -1;
		}
		break;
	case KEY_PAUSE:
		if (!game.game_over) {
			game.is_paused = !game.is_paused;
		}
		break;
	case KEY_RESTART:
		if (game.game_over || game.is_paused) {
			startGame(game);
		}
		break;
	}
}

void handleKeyRelease(GameData& game, SDL_Keycode key) {
	
    (void)game;
    (void)key;
}

void handleKeyboard(GameData& game) {
	
    if (game.is_paused || game.game_over) return;
    
	const bool* keystate = SDL_GetKeyboardState(nullptr);

	float desired_velosity = 0.0f;
    if (keystate[SDL_SCANCODE_A]) {
		
		desired_velosity -= PLATFORM_SPEED;
			
	}
	
    if (keystate[SDL_SCANCODE_D]) {
		
		desired_velosity += PLATFORM_SPEED;
    }

	game.platform.velocity_x = desired_velosity;
}
