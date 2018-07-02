#include "menu.h"



menu::menu()
{

}

menu::menu(SDL_Renderer* renderer)
{
	selItem = 0;
	
	menu_item* temp = new menu_item("Paused",62, 112, 100, 10, renderer);
	items.emplace_back(temp);
}


menu::~menu()
{
}
