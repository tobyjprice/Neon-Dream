#include "menu_main.h"
#include <iostream>


menu_main::menu_main()
{
}

menu_main::menu_main(SDL_Renderer* renderer)
{
	selItem = 0;
	
	menu_item* temp = new menu_item("Play", 62, 112, 80, 20, renderer);
	items.emplace_back(temp);
	menu_item* temp2 = new menu_item("Options", 62, 142, 100, 20, renderer);
	items.emplace_back(temp2);
	menu_item* temp3 = new menu_item("Quit", 62, 172, 60, 20, renderer);
	items.emplace_back(temp3);
}

void menu_main::update(int input, int* output)
{
	items[selItem]->set_default();
	if (input == 1)
	{
		if (selItem == 0)
		{
			selItem = items.size() - 1;
		}
		else
		{
			selItem -= 1;
		}
	}
	else if (input == 3)
	{
		if (selItem == items.size() - 1)
		{
			selItem = 0;
		}
		else
		{
			selItem += 1;
		}
	}
	else if (input == 5)
	{
		*output = selItem;
	}
	std::cout << "Selected Item - " << selItem << std::endl;

	items[selItem]->set_highlight();
}

menu_main::~menu_main()
{
}
