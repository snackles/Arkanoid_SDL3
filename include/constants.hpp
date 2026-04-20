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
	PLATFORM
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

constexpr int UI_WIDHT = 600;
constexpr int UI_HEIGHT = 100;

constexpr SDL_Color COLOR_BACKGROUND = {211, 211, 211, 255};

#endif
