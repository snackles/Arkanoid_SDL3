#include "../include/arkanoid.hpp"

#include "SDL3_image/SDL_image.h"

bool initGame(GameData &game){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);	

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

	game.platform.position.x = ((BOARD_WIDTH * BLOCK_SIZE) / 2) - ((PLATFORM_WIDTH * BLOCK_SIZE) / 2) + WALL_WIDTH;
	game.platform.position.y = (BOARD_OFFSET_Y + (BOARD_HEIGHT * BLOCK_SIZE)) - (PLATFORM_HEIGHT * BLOCK_SIZE);

	game.ball.position.x = game.platform.position.x + (PLATFORM_WIDTH * 5 - (BALL_SIZE / 2));
	game.ball.position.y = (WINDOW_HEIGHT - (PLATFORM_HEIGHT * BLOCK_SIZE) - BALL_SIZE);

	game.ball.state = 0;
	game.game_over = false;
	game.is_paused = false;
	game.is_running = true;
	game.move_speed = INITIAL_MOVE_SPEED;
	game.speed_timer = 0.0f;

	return true;
}

void initTextures(GameData &game){
	game.textures.board_background = loadTexture(game.renderer, "../assets/Test_background.png");
	game.textures.walls = loadTexture(game.renderer, "../assets/Wall_block.png");
	game.textures.platform = loadTexture(game.renderer, "../assets/Platform.png");
	game.textures.ball = loadTexture(game.renderer, "../assets/Ball.png");
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
	SDL_DestroyTexture(game.textures.platform);
	SDL_DestroyTexture(game.textures.ball);
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
}

Platform createPlatform(){
	Platform platform;
	platform.position.x = ((BOARD_WIDTH * BLOCK_SIZE) / 2) - ((PLATFORM_WIDTH * BLOCK_SIZE) / 2) + WALL_WIDTH;
	return platform;
}

bool movePlatform(Platform &platform, int dx) {
	Platform test_platform = platform;
	test_platform.position.x += dx * BLOCK_SIZE;

	if(!checkCollision(test_platform)){
		platform = test_platform;
		return true;
		}
    return false;
}

bool checkCollision(Platform &platform){
	if ((platform.position.x <= BOARD_OFFSET_X) ||
		(platform.position.x + (PLATFORM_WIDTH * BLOCK_SIZE)) >= (BOARD_OFFSET_X + (BOARD_WIDTH * BLOCK_SIZE))){
		return true;
	}
	return false;
}

bool checkCollision(Platform &platform, Ball &ball){
	if((ball.position.x <= BOARD_OFFSET_X) ||
	   (ball.position.x + BALL_SIZE >= (BOARD_OFFSET_X + (BOARD_WIDTH * BALL_SIZE))) ||
	   (ball.position.y <= BOARD_OFFSET_Y) ||
	   ((ball.position.y + BALL_SIZE >= platform.position.y) &&
		(ball.position.x >= platform.position.x) &&
		(ball.position.x <= (platform.position.x + PLATFORM_WIDTH * BLOCK_SIZE)))
		){
		return true;
	}
	return false;
}

Ball createBall(Platform &platform){
	Ball ball;
	ball.position.x = (PLATFORM_WIDTH - platform.position.x) * 5;
	ball.position.y = (PLATFORM_HEIGHT - BALL_SIZE);
	return ball;
}

bool moveBall(Ball &ball, Platform &platform, float dt){
	Ball test_ball = ball;
	test_ball.position.x += ball.direction.x * dt;
	test_ball.position.y += ball.direction.y * dt;

	if(!checkCollision(platform, test_ball)){
		ball = test_ball;
		return true;
	}
		
	if(checkCollision(platform, test_ball)){
		ball.direction.x *= -1;
		ball.direction.y *= -1;
		return true;
	 }
	
	return false;
}

void updateGame(GameData &game, float dt){
	game.speed_timer += dt;
	game.move_speed = dt * 400.0f;

	if (game.ball.state == 1){
		moveBall(game.ball, game.platform, game.move_speed);
	}
}
