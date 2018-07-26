#pragma once
#include "sprite.h"
#include "input.h"

class Player :
	public sprite
{
public:
	Player(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Surface* inSurface2, SDL_Surface* inSurface3, SDL_Renderer* renderer, std::vector<int>* inMapGrid, Input* iManager);
	~Player();
private:
	Input* inputManager;
	void get_input();
};

