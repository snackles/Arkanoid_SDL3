#include "constants.hpp"

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <string>

struct Point{
	
	float x;
	float y;
};

struct Ball{
	
	Point position;
	Point direction;
	int   state;
};

struct Platform{
	
    Point position;
};

struct Block{
	
	int   type;
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
	SDL_Texture *texture_score;
	SDL_Texture *texture_level;
};

struct GameData{
	
	SDL_Window   *window;
	SDL_Renderer *renderer;
	TTF_Font     *font;
	
	Textures  textures;
	GameBoard board;
	Platform  platform;
	Ball      ball; 
	Block     block;

	std::vector<Block> blocks;
	
	bool game_over;
	bool is_paused;
    bool is_running;
	int  game_state;
	int  score;
	int  level;

	float move_speed;

	uint32_t last_time;
    float    delta_time;
};

bool initGame(GameData &game);
void renderGame(GameData &game);
void initTextures(GameData &game);

void startGame(GameData &game);
bool movePlatform(Platform &platform, int dx);
bool moveBall(GameData &game);

bool checkCollision(Platform &platform);
bool checkCollision(Platform &platform, Ball &ball);
bool checkCollision(Block &block, Ball &ball);

void updateGame(GameData &game, float dt);
void updateText(GameData &game);

Platform createPlatform();
Ball     createBall(Platform &platform);
Block    createBlock(GameBoard &board);

void drawBoard(GameData &game);
void drawWalls(GameData &game);
void drawPlatform(GameData &game, Platform &platform);
void drawBall(GameData &game, Ball &ball);
void drawBlock(GameData &game, Block &block);
void drawUI(GameData &game);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void destroyObjects(GameData &game);

void processEvent(GameData &game);
void handleKeyPress(GameData& game, SDL_Keycode key);
void handleKeyRelease(GameData& game, SDL_Keycode key);
void handleKeyboard(GameData& game, float dt);

