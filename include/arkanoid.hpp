#include "constants.hpp"
#include <array>
#include <vector>

struct Point{
	int x;
	int y;
};

struct Platform{
	float position;
	std::array<Point, 4> ABCD;
	double move_speed;
};

struct GameBoard{
	int width;
	int height;
};

struct Textures{
	SDL_Texture *board_background;
	SDL_Texture *walls;
	SDL_Texture *platform;
};

struct GameData{
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	Textures textures;
	GameBoard board;
	Platform platform;

	int game_state;
	bool game_over;
	bool is_paused;
    bool is_running;
};

bool initGame(GameData &game);
void renderGame(GameData &game);
void initTextures(GameData &game);

Platform createPlatform();

void drawBoard(GameData &game);
void drawWalls(GameData &game);
void drawPlatform(GameData &game);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void destroyObjects(GameData &game);
