#include "options_menu.h"



options_menu::options_menu()
{
}

options_menu::options_menu(SDL_Renderer* renderer)
{
	selItem = 0;

	menu_item* temp = new menu_item("Fullscreen - Inactive", 62, 112, 140, 20, renderer);
	items.emplace_back(temp);
	menu_item* temp2 = new menu_item("thing2", 62, 142, 100, 20, renderer);
	items.emplace_back(temp2);
	menu_item* temp3 = new menu_item("Back", 62, 172, 60, 20, renderer);
	items.emplace_back(temp3);
}

void options_menu::update(int input, int* output)
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
		if (selItem == 0)
		{
			if (items[selItem]->value == 0)
			{
				items[selItem]->set_text("Fullscreen - Active");
				*output = selItem;
			}
			else if (items[selItem]->value == 1)
			{
				items[selItem]->set_text("Fullscreen - Inactive");
				*output = selItem;
			}
		}
		else if (selItem == 1)
		{
			*output = 1;
		}
		else if (selItem == 2)
		{
			*output = selItem;
			selItem = 0;
		}
	}

	items[selItem]->set_highlight();
}

options_menu::~options_menu()
{
}
