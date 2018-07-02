#pragma once
#include "menu.h"

class options_menu :
	public menu
{
public:
	options_menu();
	options_menu(SDL_Renderer* renderer);
	~options_menu();

	void update(int input, int* output);
};

