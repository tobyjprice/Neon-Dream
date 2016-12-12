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
	int getArrPos(int i, int j, int width);
	sprite* getSprite(int spriteId);
	bool game_state::checkCollision(sprite* one, sprite* two);

	SDL_Renderer* gameRenderer;
	std::vector<sprite*> spriteList;
	std::vector<int> mapGrid;
	int mapWidth, mapHeight;
private:
	
};

