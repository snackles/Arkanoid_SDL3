#include "constants.hpp"
//#include <array>
//#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

struct Point{
	
	float x;
	float y;
};

struct Ball{
	
	Point position;
	Point direction;
	int state;
};

struct Platform{
	
    Point position;
};

struct Block{
	
	int type;
	Point position;
};

struct GameBoard{
	
	int width;
	int height;
	std::vector<std::vector<int>> grid;
};

struct Textures{
	
	SDL_Texture *board_background;
	SDL_Texture *walls;
	SDL_Texture *platform;
	SDL_Texture *ball;
 	SDL_Texture *base_block_azure;
	SDL_Texture *base_block_blue;
	SDL_Texture *base_block_green;
	SDL_Texture *base_block_pink;
	SDL_Texture *base_block_purple;
	SDL_Texture *base_block_red;
	SDL_Texture *base_block_yellow;
	SDL_Texture *double_shot_block;
	SDL_Texture *strong_block;
};

struct GameData{
	
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	Textures textures;
	GameBoard board;
	Platform platform;
	Ball ball;
	Block block;

	std::vector<Block> blocks;
	
	int game_state;
	bool game_over;
	bool is_paused;
    bool is_running;

	float move_speed;

	uint32_t last_time;
    float delta_time;
};

bool initGame(GameData &game);
void renderGame(GameData &game);
void initTextures(GameData &game);
bool movePlatform(Platform &platform, int dx);
bool moveBall(Ball &ball, Platform &platform, float move_speed);
bool checkCollision(Platform &platform);
bool checkCollision(Platform &platform, Ball &ball);
void updateGame(GameData &game, float dt);

Platform createPlatform();
Ball createBall(Platform &platform);
Block createBlock(GameBoard &board);

void drawBoard(GameData &game);
void drawWalls(GameData &game);
void drawPlatform(GameData &game, Platform &platform);
void drawBall(GameData &game, Ball &ball);
void drawBlock(GameData &game, Block &block);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void destroyObjects(GameData &game);

void processEvent(GameData &game);
void handleKeyPress(GameData& game, SDL_Keycode key);
void handleKeyRelease(GameData& game, SDL_Keycode key);
void handleKeyboard(GameData& game, float dt);

