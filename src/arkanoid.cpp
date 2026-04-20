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

	if (game.window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
    }
	
	game.renderer = SDL_CreateRenderer(game.window, nullptr);
	initTextures(game);
	
	game.board.width = BOARD_WIDTH;
	game.board.height = BOARD_HEIGHT;

	game.platform.position = ((BOARD_WIDTH * BLOCK_SIZE) / 2) - ((PLATFORM_WIDTH * BLOCK_SIZE) / 2) + WALL_WIDTH;

	return true;
}

void initTextures(GameData &game){
	game.textures.board_background = loadTexture(game.renderer, "../assets/Test_background.png");
	game.textures.walls = loadTexture(game.renderer, "../assets/Wall_block.png");
	game.textures.platform = loadTexture(game.renderer, "../assets/Platform.png");
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
	SDL_DestroyTexture(game.textures.platform);
}

Platform createPlatform(){
	Platform platform;
	platform.position = (BOARD_WIDTH / 2) - (PLATFORM_WIDTH / 2);
	return platform;
}
