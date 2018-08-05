#include "Player.h"


Player::Player(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Surface* inSurface2, SDL_Surface* inSurface3, SDL_Renderer* renderer, std::vector<int>* inMapGrid, Input* iManager) 
	: sprite(w, h, x, y, inSurface, inSurface2, inSurface3, renderer, inMapGrid)
{
	inputManager = iManager;
}

Player::~Player()
{
}

void Player::set_pot_moves(std::vector<int> inMoves)
{
	availMoves = inMoves;
}

void Player::get_input()
{
	input = inputManager->get_current_input();
}
