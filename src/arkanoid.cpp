#include "../include/arkanoid.hpp"

#include "SDL3_image/SDL_image.h"

bool initGame(GameData &game){
	SDL_Init(SDL_INIT_VIDEO);

	game.window = SDL_CreateWindow(
		"Arkanoid",
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
		);
	game.renderer = SDL_CreateRenderer(game.window, nullptr);

	if (game.window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

	game.board.width = BOARD_WIDTH;
	game.board.height = BOARD_HEIGHT;
	game.board.grid.clear();
	game.board.grid = std::vector<std::vector<int>>(
		BOARD_HEIGHT, 
        std::vector<int>(BOARD_WIDTH, TYPE_NONE)
		);

	return true;
}

void initTextures(GameData &game){
	game.textures.board_background = loadTexture(game.renderer, "../assets/Test_background.png");
	game.textures.walls = loadTexture(game.renderer, "../assets/Wall_block.png");
}
	
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path){
	SDL_Surface *surface = IMG_Load(path);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	return texture;
}

void destroyObjects(GameData &game){
	SDL_DestroyTexture(game.textures.board_background);
	SDL_DestroyTexture(game.textures.walls);
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
}
