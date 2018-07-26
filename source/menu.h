#pragma once
#include "menu_item.h"

class menu
{
public:
	menu();
	menu(SDL_Renderer* renderer);
	~menu();
	bool active;
	std::vector<menu_item*> items;
	int selItem;
	TTF_Font* font;
};

