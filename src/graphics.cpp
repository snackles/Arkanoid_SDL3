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

	for (unsigned int i = 0; i < game.blocks.size(); ++i){
		
		drawBlock(game, game.blocks[i]);
	}

	SDL_RenderPresent(game.renderer);
}

void drawBoard(GameData &game){
	
	SDL_FRect board_bg{
		BOARD_OFFSET_X,
		BOARD_OFFSET_Y,
		BOARD_WIDTH * GRID_BLOCK_SIZE,
		BOARD_HEIGHT * GRID_BLOCK_SIZE
	};
	SDL_RenderTexture(game.renderer, game.textures.board_background, NULL, &board_bg);
}

void drawWalls(GameData &game){
	
	SDL_FRect left_wall{
		0,
		BOARD_OFFSET_Y - WALL_WIDTH,
		WALL_WIDTH,
		BOARD_HEIGHT * GRID_BLOCK_SIZE + WALL_WIDTH
	};
	SDL_RenderTexture(game.renderer, game.textures.walls, NULL, &left_wall);

	SDL_FRect top_wall{
		BOARD_OFFSET_X,
		BOARD_OFFSET_Y - WALL_WIDTH,
		BOARD_WIDTH * GRID_BLOCK_SIZE,
		WALL_WIDTH
	};
	SDL_RenderTexture(game.renderer, game.textures.walls, NULL, &top_wall);

	SDL_FRect right_wall{
		BOARD_WIDTH * GRID_BLOCK_SIZE + BOARD_OFFSET_X,
		BOARD_OFFSET_Y - WALL_WIDTH,
		WALL_WIDTH,
		BOARD_HEIGHT * GRID_BLOCK_SIZE + WALL_WIDTH
	};
	SDL_RenderTexture(game.renderer, game.textures.walls, NULL, &right_wall);
}

void drawPlatform(GameData &game, Platform &platform){
	
	SDL_FRect rect_platform{
		platform.position.x,
		platform.position.y,
		PLATFORM_WIDTH * GRID_BLOCK_SIZE,
		PLATFORM_HEIGHT * GRID_BLOCK_SIZE
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

void drawBlock(GameData &game, Block &block){
	
	SDL_FRect rect_block{
		BOARD_OFFSET_X + block.position.x * GRID_BLOCK_SIZE,
		BOARD_OFFSET_Y + block.position.y * GRID_BLOCK_SIZE,
		BLOCK_WIDTH * GRID_BLOCK_SIZE,
		BLOCK_HEIGHT * GRID_BLOCK_SIZE
	};
	
	switch(block.type){
		
	case BASE_AZURE:
		SDL_RenderTexture(game.renderer, game.textures.base_block_azure, NULL, &rect_block);
		break;
	case BASE_BLUE:
		SDL_RenderTexture(game.renderer, game.textures.base_block_blue, NULL, &rect_block);
		break;
	case BASE_GREEN:
		SDL_RenderTexture(game.renderer, game.textures.base_block_green, NULL, &rect_block);
		break;
	case BASE_PINK:
		SDL_RenderTexture(game.renderer, game.textures.base_block_pink, NULL, &rect_block);
		break;
	case BASE_PURPLE:
		SDL_RenderTexture(game.renderer, game.textures.base_block_purple, NULL, &rect_block);
		break;
	case BASE_RED:
		SDL_RenderTexture(game.renderer, game.textures.base_block_red, NULL, &rect_block);
		break;
	case BASE_YELLOW:
		SDL_RenderTexture(game.renderer, game.textures.base_block_yellow, NULL, &rect_block);
		break;
	case DOUBLE_SHOT:
		SDL_RenderTexture(game.renderer, game.textures.double_shot_block, NULL, &rect_block);
		break;
	case STRONG:
		SDL_RenderTexture(game.renderer, game.textures.strong_block, NULL, &rect_block);
		break;
	}
}






