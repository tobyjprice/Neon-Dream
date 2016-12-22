#pragma once
#include "sprite.h"

class ghost : public sprite
{
public:
	ghost();
	ghost(int x, int y, int w, int h, SDL_Surface* inSurface, SDL_Surface* inSurface2, SDL_Surface* inSurface3, SDL_Renderer* renderer);
	void update(double dt, std::vector<int>* mapGrid, int tick);
	~ghost();
};

