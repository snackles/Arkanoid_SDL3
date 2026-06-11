#include <vector>

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

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
	float velocity_x;
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
	SDL_Event     event;
	
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

bool initGame    (GameData &game);
void renderGame  (GameData &game);
void initTextures(Textures &textures, SDL_Renderer *renderer);

void startGame   (GameData &game);
void postPlatform(Platform &platform);
void postBall    (Platform &platform, Ball &ball);
bool moveBall    (GameData &game, float dt);

bool checkCollision(Platform &platform);
bool checkCollision(Platform &platform, Ball &ball);
bool checkCollision(Block &block, Ball &ball);

void updateGame    (GameData &game, float dt);
void updateText    (GameData &game);
void updatePlatform(GameData &game, float dt);

Block createBlock (GameBoard &board);

void drawBoard   (SDL_Renderer *renderer, Textures &textures);
void drawWalls   (SDL_Renderer *renderer, Textures &textures);
void drawPlatform(SDL_Renderer *renderer, Textures &textures, Platform &platform);
void drawBall    (SDL_Renderer *renderer, Textures &textures, Ball &ball);
void drawBlock   (SDL_Renderer *renderer, Textures &textures, Block &block);
void drawUI      (SDL_Renderer *renderer, Textures &textures);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void destroyObjects     (GameData &game);

void processEvent    (GameData &game);
void handleKeyPress  (GameData& game, SDL_Keycode key);
void handleKeyRelease(GameData& game, SDL_Keycode key);
void handleKeyboard  (GameData& game);

