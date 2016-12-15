#pragma once
#include <vector>
#include "sprite.h"
#include "mapPoint.h"

class game_state
{
public:
	game_state(SDL_Renderer *renderer);
	~game_state();
	void load_resources();
	void load_map();
	void populate_map();
	SDL_Surface* getWallSurface(int x, int y, int width);
	int getArrPos(int i, int j, int width);
	sprite* getSprite(int spriteId);
	bool game_state::checkCollision(sprite* one, sprite* two);

	SDL_Renderer* gameRenderer;
	std::vector<sprite*> spriteList;
	std::vector<int> mapGrid;
	int mapWidth, mapHeight;
private:
	SDL_Surface* playerSurface;
	SDL_Surface* bottomLeft;
	SDL_Surface* bottomRight;
	SDL_Surface* topLeft;
	SDL_Surface* topRight;
	SDL_Surface* horiBottom;
	SDL_Surface* horiTop;
	SDL_Surface* vertLeft;
	SDL_Surface* vertRight;
};

