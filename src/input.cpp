#include "../include/arkanoid.hpp"

SDL_Event event;

void processEvent(GameData &game){		
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
		case SDL_EVENT_QUIT:
			game.is_running = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			handleKeyPress(game, event.key.key);
			break;
		case SDL_EVENT_KEY_UP:
			handleKeyRelease(game, event.key.key);
			break;
		}
	}
	handleKeyboard(game, game.delta_time);
}

void handleKeyPress(GameData& game, SDL_Keycode key) {
    if (event.key.repeat) {
        return;
    }
    switch (key) {
	case KEY_QUIT:
		game.is_running = false;
		break;
	case KEY_START:
		game.ball.state = 1;
		game.ball.direction.x = 0;
		game.ball.direction.y = -1;
		break;
	// case KEY_PAUSE:
	// 	if (!game.game_over) {
	// 		game.is_paused = !game.is_paused;
	// 	}
	// 	break;
	// case KEY_RESTART:
	// 	if (game.game_over || game.is_paused) {
	// 		reset_game(game);
	// 	}
	// 	break;
	}
}

void handleKeyRelease(GameData& game, SDL_Keycode key) {
    (void)game;
    (void)key;
}


void handleKeyboard(GameData& game, float dt) {
    if (game.is_paused || game.game_over) return;

    static float left_timer = 0.0f;
    static float right_timer = 0.0f;

    static bool left_was_pressed = false;
    static bool right_was_pressed = false;
    
	const bool* keystate = SDL_GetKeyboardState(nullptr);

    if (keystate[SDL_SCANCODE_A]) {
        if (!left_was_pressed || left_timer >= DAS_DELAY) {
            float move_rate = left_was_pressed ? DAS_SPEED : 0.0f;
            if (left_timer >= move_rate) {
                if(movePlatform(game.platform, -1)){}
                left_timer = 0.0f;
            }
        }
        left_timer += dt;
        left_was_pressed = true;
    } else {
        left_was_pressed = false;
        left_timer = 0.0f;
    }
    
    if (keystate[SDL_SCANCODE_D]) {
        if (!right_was_pressed || right_timer >= DAS_DELAY) {
            float move_rate = right_was_pressed ? DAS_SPEED : 0.0f;
            if (right_timer >= move_rate) {
				if(movePlatform(game.platform, 1)){}
				right_timer = 0.0f;
            }
        }
        right_timer += dt;
        right_was_pressed = true;
    } else {
        right_was_pressed = false;
        right_timer = 0.0f;
    }
}
