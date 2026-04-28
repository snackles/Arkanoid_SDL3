#ifndef ARKANOID_CONSTANTS_HPP
#define ARKANOID_CONSTANTS_HPP

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

enum BlockType{
	TYPE_NONE,
	BASE,
	DOUBLE_SHOT,
	STRONG,
};

enum BallState{
	BALL_ATTACHED,
	BALL_FLYING
};

enum GameState{
	STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER
};
// Window settings
constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 800;

// Board settings
constexpr int BOARD_WIDTH = 54;
constexpr int BOARD_HEIGHT = 67;
constexpr int BOARD_OFFSET_X = 30;
constexpr int BOARD_OFFSET_Y = 130;

constexpr int BLOCK_SIZE = 10;
constexpr int WALL_WIDTH = 30;

constexpr int PLATFORM_WIDTH = 8;
constexpr int PLATFORM_HEIGHT = 4;

constexpr int BALL_SIZE = 10;

constexpr int UI_WIDHT = 600;
constexpr int UI_HEIGHT = 100;

constexpr SDL_Color COLOR_BACKGROUND = {211, 211, 211, 255};

constexpr SDL_Keycode KEY_MOVE_LEFT = SDLK_A;
constexpr SDL_Keycode KEY_MOVE_RIGHT = SDLK_D;
constexpr SDL_Keycode KEY_QUIT = SDLK_ESCAPE;
constexpr SDL_Keycode KEY_START = SDLK_SPACE;

constexpr float INITIAL_MOVE_SPEED = 1000.0f;

constexpr float FRAME_TIME = 1.0f / 60.0f;
constexpr float DAS_DELAY = 0.09f;        
constexpr float DAS_SPEED = 0.04f;    

#endif
