#include "Player.h"


Player::Player(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Surface* inSurface2, SDL_Surface* inSurface3, SDL_Renderer* renderer, std::vector<int>* inMapGrid) 
	: sprite(w, h, x, y, inSurface, inSurface2, inSurface3, renderer, inMapGrid)
{

}


Player::~Player()
{
}
