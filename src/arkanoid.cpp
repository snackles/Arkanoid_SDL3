#include "../include/arkanoid.hpp"

#include "SDL3_image/SDL_image.h"
#include <string>
#include <vector>

static std::mt19937 gen(std::random_device{}());

bool initGame(GameData &game){
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	TTF_Init();

	game.window = SDL_CreateWindow(
		"Arkanoid",
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
		);

	if (game.window == nullptr) {
		
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
					 "Could not create window: %s\n",
					 SDL_GetError());
		return 1;
    }
	
	game.renderer = SDL_CreateRenderer(game.window, nullptr);
	initTextures(game);

	// Font initialize
	game.font = TTF_OpenFont("../assets/Tetris.ttf", 24);

	// Board initialize
	game.board.width  = BOARD_WIDTH;
	game.board.height = BOARD_HEIGHT / 2;

	game.score = 0;
	game.level = 0;

	startGame(game);
	
	return true;
}

void updateText(GameData &game){

	std::string score_text = "Score: " + std::to_string(game.score);
	std::string level_text = "Level: " + std::to_string(game.level);

	SDL_Surface* score_surface = TTF_RenderText_Blended(game.font,
														score_text.c_str(),
														score_text.length(),
														TEXT_COLOR);
	game.textures.texture_score = SDL_CreateTextureFromSurface(game.renderer, score_surface);
	SDL_DestroySurface(score_surface);
	
	SDL_Surface* level_surface = TTF_RenderText_Blended(game.font,
														level_text.c_str(),
														level_text.length(),
														TEXT_COLOR);
	game.textures.texture_level = SDL_CreateTextureFromSurface(game.renderer, level_surface);
	SDL_DestroySurface(level_surface);
}

void initTextures(GameData &game){
	
	game.textures.board_background         = loadTexture(game.renderer,
														 "../assets/Test_background.png");
	game.textures.walls                    = loadTexture(game.renderer,
														 "../assets/Wall_block.png");
	game.textures.platform                 = loadTexture(game.renderer,
														 "../assets/Platform.png");
	game.textures.ball                     = loadTexture(game.renderer,
														 "../assets/Ball.png");
	game.textures.base_block_azure         = loadTexture(game.renderer,
														 "../assets/Base_block_azure.png");
	game.textures.base_block_blue          = loadTexture(game.renderer,
														"../assets/Base_block_blue.png");
	game.textures.base_block_green         = loadTexture(game.renderer,
														"../assets/Base_block_green.png");
	game.textures.base_block_pink          = loadTexture(game.renderer,
														"../assets/Base_block_pink.png");
	game.textures.base_block_purple        = loadTexture(game.renderer,
														"../assets/Base_block_purple.png");
	game.textures.base_block_red           = loadTexture(game.renderer,
														"../assets/Base_block_red.png");
	game.textures.base_block_yellow        = loadTexture(game.renderer,
														"../assets/Base_block_yellow.png");
	game.textures.double_shot_block        = loadTexture(game.renderer,
														 "../assets/Double_shot_block.png"); 
	game.textures.strong_block             = loadTexture(game.renderer,
														 "../assets/Strong_block.png"); 
}
	
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path){
	
	SDL_Surface *surface = IMG_Load(path);	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	return texture;
}

void destroyObjects(GameData &game){
	
	SDL_DestroyTexture (game.textures.board_background);
	SDL_DestroyTexture (game.textures.walls);
	SDL_DestroyTexture (game.textures.platform);
	SDL_DestroyTexture (game.textures.ball);
	SDL_DestroyTexture (game.textures.base_block_azure);
	SDL_DestroyTexture (game.textures.base_block_blue);
	SDL_DestroyTexture (game.textures.base_block_green);
	SDL_DestroyTexture (game.textures.base_block_pink);
	SDL_DestroyTexture (game.textures.base_block_purple);
	SDL_DestroyTexture (game.textures.base_block_red);
	SDL_DestroyTexture (game.textures.base_block_yellow);
	SDL_DestroyTexture (game.textures.double_shot_block);
	SDL_DestroyTexture (game.textures.strong_block);
	SDL_DestroyTexture (game.textures.texture_score);
	SDL_DestroyTexture (game.textures.texture_level);
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow  (game.window);
}

void startGame(GameData &game){

	game.board.grid.clear();
	game.board.grid = std::vector<std::vector<int>>(
		game.board.width, 
        std::vector<int>(game.board.height, TYPE_NONE)
		);

	// Platform start position
	game.platform.position.x = BOARD_OFFSET_X +
		((BOARD_WIDTH * GRID_BLOCK_SIZE) / 2) -
		((PLATFORM_WIDTH * GRID_BLOCK_SIZE) / 2);
	
	game.platform.position.y = BOARD_OFFSET_Y +
		(BOARD_HEIGHT * GRID_BLOCK_SIZE) -
		(PLATFORM_HEIGHT * GRID_BLOCK_SIZE); 

	// Ball start position
	game.ball.position.x = game.platform.position.x +
		(PLATFORM_WIDTH * GRID_BLOCK_SIZE) / 2 -
		BALL_SIZE / 2;
	
	game.ball.position.y = game.platform.position.y -
		BALL_SIZE;

	// Block generation
	game.blocks.clear();
	
	static std::uniform_int_distribution<int> block_quantity(15, 25);
	unsigned int number_of_blocks = block_quantity(gen);
	
	for (unsigned int i = 0; i < number_of_blocks; ++i){
		
		game.blocks.push_back(createBlock(game.board));
	}
	
	for (unsigned int i = 0; i < number_of_blocks; ++i){
		
		Block block = game.blocks[i];

		if (block.position.x < ((game.board.width / 2) - ((game.board.width / 2) % 5))){
			
			block.position.x = game.board.width - block.position.x - BLOCK_WIDTH;
			game.blocks.push_back(block);
		}
	}

	// GameData initialize
	if (game.game_over){

		game.score = 0;
		game.level = 0;
	}
	game.game_state = 1;
	game.ball.state = 0;
	game.game_over  = false;
	game.is_paused  = false;
	game.is_running = true;
	game.move_speed = INITIAL_MOVE_SPEED;
}

Platform createPlatform(){
	
	Platform platform;
	
	platform.position.x = ((BOARD_WIDTH * GRID_BLOCK_SIZE) / 2) -
		((PLATFORM_WIDTH * GRID_BLOCK_SIZE) / 2) + WALL_WIDTH;
	
	return platform;
}

bool movePlatform(Platform &platform, int dx) {
	
	Platform test_platform = platform;
	test_platform.position.x += dx * GRID_BLOCK_SIZE;

	if(!checkCollision(test_platform)){
		
		platform = test_platform;

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

Block createBlock(GameBoard &board){
	
	static std::uniform_int_distribution<int> block_type(1, 9);
	Block block;
	block.type = block_type(gen);

	bool free_block = false;
	while(!free_block){

		std::uniform_int_distribution<int> block_position_x(0, board.width / 2);
		std::uniform_int_distribution<int> block_position_y(0, board.height);
		int x = block_position_x(gen);
		int y = block_position_y(gen);
		x     = x - (x % BLOCK_WIDTH);
		y     = y - (y % BLOCK_HEIGHT);

		free_block = true;
		
		for (int j = 0; j < BLOCK_WIDTH; ++j){
			
			for (int i = 0; i < BLOCK_HEIGHT; ++i) {
				
				if (board.grid[x + j][y + i] != TYPE_NONE){
					
					free_block = false;
					break;
				}
			}
			if (!free_block) break;
		}

		if (free_block) {
			
			for (int j = 0; j < BLOCK_WIDTH; ++j){
				
				for (int i = 0; i < BLOCK_HEIGHT; ++i){
					
					board.grid[x + j][y + i] = block.type;
				}
			}
			block.position.x = x;
            block.position.y = y;
		}
	}
	return block;
}

bool moveBall(GameData &game){

	float offset;
	float normalized;
	float angle;
	Ball test_ball = game.ball;
	test_ball.position.x += game.ball.direction.x * game.move_speed;
	test_ball.position.y += game.ball.direction.y * game.move_speed;

	for (unsigned int i = 0; i < game.blocks.size(); ++i){

		if (checkCollision(game.blocks[i], test_ball)){

			float eps = std::ceil(game.move_speed);

			test_ball.position.y += eps;
			if (!checkCollision(game.blocks[i], test_ball)){

				game.ball.direction.y *= -1;		
			}
			test_ball.position.y -= eps;

			test_ball.position.y -= eps;
			if (!checkCollision(game.blocks[i], test_ball)){

				game.ball.direction.y *= -1;
			}
			test_ball.position.y += eps;

			test_ball.position.x -= eps;
			if (!checkCollision(game.blocks[i], test_ball)){

				game.ball.direction.x *= -1;
			}
			test_ball.position.x += eps;

			test_ball.position.x += eps;
			if (!checkCollision(game.blocks[i], test_ball)){

				game.ball.direction.x *= -1;
			}
			test_ball.position.x -= eps;

			if (game.blocks[i].type == DOUBLE_SHOT){

				static std::uniform_int_distribution<int> block_type(1, 7);
				game.blocks[i].type = block_type(gen);
				game.score += POINTS_PER_BLOCK;
				return true;
			}
			
			if (game.blocks[i].type != STRONG){
				
				game.blocks.erase(game.blocks.begin() + i);
				game.score += POINTS_PER_BLOCK;
				--i;
			}
			return true;
		}
	}

	if(checkCollision(game.platform, test_ball)){

		if (test_ball.position.y + BALL_SIZE >= game.platform.position.y){
			
			offset = (game.ball.position.x + (BALL_SIZE / 2)) -
				(game.platform.position.x + ((PLATFORM_WIDTH * GRID_BLOCK_SIZE) / 2));
			
			normalized = offset / ((PLATFORM_WIDTH * GRID_BLOCK_SIZE) / 2);
			
			if (normalized < 0.05){ normalized += 0.05; }
			
			angle = MAX_ANGLE * normalized;
			
			game.ball.direction.x = std::sin(angle);
			game.ball.direction.y = -1 * std::cos(angle);
			
		} else if (test_ball.position.x + BALL_SIZE >=
			(BOARD_OFFSET_X + (BOARD_WIDTH * GRID_BLOCK_SIZE))
			||
			(test_ball.position.x <= BOARD_OFFSET_X)){
			
			game.ball.direction.x *= -1;
			
		} else {
			
			game.ball.direction.y *= -1;
		}
		return true;
	}

	if (game.ball.position.y + BALL_SIZE >
		BOARD_OFFSET_Y + (BOARD_HEIGHT * GRID_BLOCK_SIZE)){

		game.game_over = true;
	}
	
	if(!checkCollision(game.platform, test_ball)){

		game.ball = test_ball;
		return true;
	}
	return false;
}

bool checkCollision(Platform &platform){
	
	if ((platform.position.x <= BOARD_OFFSET_X) ||
		(platform.position.x + (PLATFORM_WIDTH * GRID_BLOCK_SIZE)) >=
		(BOARD_OFFSET_X + (BOARD_WIDTH * GRID_BLOCK_SIZE))){
		
		return true;
	}
	return false;
}

bool checkCollision(Platform &platform, Ball &ball){
	
	if((ball.position.x <= BOARD_OFFSET_X) ||
	   (ball.position.x + BALL_SIZE >= (BOARD_OFFSET_X + (BOARD_WIDTH * GRID_BLOCK_SIZE))) ||
	   (ball.position.y <= BOARD_OFFSET_Y) ||
	   ((ball.position.y + BALL_SIZE >= platform.position.y) &&
		(ball.position.x >= platform.position.x) &&
		(ball.position.x <= (platform.position.x + PLATFORM_WIDTH * GRID_BLOCK_SIZE)))
		){
		
		return true;
	}
	return false;
}

bool checkCollision(Block &block, Ball &ball){

	if (ball.position.x + BALL_SIZE >=
		block.position.x * GRID_BLOCK_SIZE + BOARD_OFFSET_X &&
		ball.position.y + BALL_SIZE >=
		block.position.y * GRID_BLOCK_SIZE + BOARD_OFFSET_Y &&
		ball.position.x <=
		(block.position.x + BLOCK_WIDTH) * GRID_BLOCK_SIZE  + BOARD_OFFSET_X &&
		ball.position.y <=
		(block.position.y + BLOCK_HEIGHT) * GRID_BLOCK_SIZE + BOARD_OFFSET_Y){
	
		return true;
	}

	return false;
}

void updateGame(GameData &game, float dt){

	if (game.game_over){
  
		game.game_state = STATE_GAME_OVER;
		return;
	}

	game.move_speed = dt * 300.0f;

	if (game.ball.state == 1){
		
		moveBall(game);
	}

	updateText(game);
	int counter = 0;
	for (unsigned int i = 0; i < game.blocks.size(); ++i){
		
		if (game.blocks[i].type > 0 && game.blocks[i].type < 9){

			counter += 1;
		}
	}
	
	if (counter == 0){

		game.level += 1;
		startGame(game);
	}
}
