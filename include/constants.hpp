#ifndef ARKANOID_CONSTANTS_HPP
#define ARKANOID_CONSTANTS_HPP

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

enum BlockType{
	
	TYPE_NONE,
	BASE_AZURE,
	BASE_BLUE,
	BASE_GREEN,
	BASE_PINK,
	BASE_PURPLE,
	BASE_RED,
	BASE_YELLOW,
	DOUBLE_SHOT,
	STRONG,
	PADDING
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
constexpr int WINDOW_WIDTH = 610;
constexpr int WINDOW_HEIGHT = 800;

// Board settings
constexpr int WALL_WIDTH = 30;
constexpr int BOARD_WIDTH = 55;
constexpr int BOARD_HEIGHT = 67;
constexpr int BOARD_OFFSET_X = 30;
constexpr int BOARD_OFFSET_Y = 130;
constexpr int GRID_BLOCK_SIZE = 10;

// Block settings
constexpr int BLOCK_WIDTH = 5;
constexpr int BLOCK_HEIGHT = 3;

// Platform settings
constexpr int PLATFORM_WIDTH = 8;
constexpr int PLATFORM_HEIGHT = 4;

// Ball settings
constexpr int BALL_SIZE = 10;
constexpr float MAX_ANGLE = 1.047;

// UI settings
constexpr int UI_WIDHT = 600;
constexpr int UI_HEIGHT = 100;

// Colors
constexpr SDL_Color COLOR_BACKGROUND = {211, 211, 211, 255};

// Keys
constexpr SDL_Keycode KEY_MOVE_LEFT = SDLK_A;
constexpr SDL_Keycode KEY_MOVE_RIGHT = SDLK_D;
constexpr SDL_Keycode KEY_QUIT = SDLK_ESCAPE;
constexpr SDL_Keycode KEY_START = SDLK_SPACE;

// Game states
constexpr float INITIAL_MOVE_SPEED = 1000.0f;

constexpr float FRAME_TIME = 1.0f / 60.0f;
constexpr float DAS_DELAY = 0.05f;        
constexpr float DAS_SPEED = 0.04f;    

#endif
