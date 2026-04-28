#include "../include/arkanoid.hpp"

void renderGame(GameData &game){
	if (game.renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "renderGame: renderer is nullptr!\n");
        return;
    }
	
	SDL_SetRenderDrawColor(game.renderer, 
						   COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, 
						   COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
    SDL_RenderClear(game.renderer);

	drawBoard(game);
	drawWalls(game);
	drawPlatform(game, game.platform);
	drawBall(game, game.ball);

	SDL_RenderPresent(game.renderer);
}

void drawBoard(GameData &game){
	SDL_FRect board_bg{
		BOARD_OFFSET_X,
		BOARD_OFFSET_Y,
		BOARD_WIDTH * BLOCK_SIZE,
		BOARD_HEIGHT * BLOCK_SIZE
	};
	SDL_RenderTexture(game.renderer, game.textures.board_background, NULL, &board_bg);
}

void drawWalls(GameData &game){
	SDL_FRect left_wall{
		0,
		UI_HEIGHT,
		WALL_WIDTH,
		BOARD_HEIGHT * BLOCK_SIZE + WALL_WIDTH
	};
	SDL_RenderTexture(game.renderer, game.textures.walls, NULL, &left_wall);

	SDL_FRect top_wall{
		WALL_WIDTH,
		UI_HEIGHT,
		BOARD_WIDTH * BLOCK_SIZE,
		WALL_WIDTH
	};
	SDL_RenderTexture(game.renderer, game.textures.walls, NULL, &top_wall);

	SDL_FRect right_wall{
		BOARD_WIDTH * BLOCK_SIZE + WALL_WIDTH,
		UI_HEIGHT,
		WALL_WIDTH,
		BOARD_HEIGHT * BLOCK_SIZE + WALL_WIDTH
	};
	SDL_RenderTexture(game.renderer, game.textures.walls, NULL, &right_wall);
}

void drawPlatform(GameData &game, Platform &platform){
	SDL_FRect rect_platform{
		platform.position.x,
		platform.position.y,
		PLATFORM_WIDTH * BLOCK_SIZE,
		PLATFORM_HEIGHT * BLOCK_SIZE
	};
	SDL_RenderTexture(game.renderer, game.textures.platform, NULL, &rect_platform);
}

void drawBall(GameData &game, Ball &ball){
	SDL_FRect rect_ball{
		ball.position.x,
		ball.position.y,
		BALL_SIZE,
		BALL_SIZE
	};
	SDL_RenderTexture(game.renderer, game.textures.ball, NULL, &rect_ball);
}
