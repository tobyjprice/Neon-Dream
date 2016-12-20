#pragma once
#include "menu.h"
class menu_main :
	public menu
{
public:
	menu_main();
	menu_main(SDL_Renderer* renderer);
	void update(int input, int* output);
	~menu_main();
};

