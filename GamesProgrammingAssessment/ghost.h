#pragma once
#include "sprite.h"

class ghost : public sprite
{
public:
	ghost();
	ghost(int x, int y, int w, int h, SDL_Surface* surface, SDL_Renderer* renderer);
	void update(double dt, sprite* collider, std::vector<int>* mapGrid);
	~ghost();
};

