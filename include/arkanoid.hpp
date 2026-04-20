#include "constants.hpp"
#include <vector>

struct Point{
	int x;
	int y;
};

struct Platform{
	Point position;
	double move_speed;
	std::array<Point, 36> blocks;
};

struct GameBoard{
	std::vector<std::vector<int>> grid;
	int width;
	int height;
};

struct Textures{
	SDL_Texture *board_background;
	SDL_Texture *walls;
};

struct GameData{
	SDL_Window *window;
	SDL_Renderer *renderer;
	Textures textures;
	GameBoard board;
	Platform platform;

	int game_state;
};

bool initGame(GameData &game);
void renderGame(GameData &game);

void drawBoard(GameData &game);
void drawWalls(GameData &game);

void initTextures(GameData &game);
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void destroyObjects(GameData &game);
