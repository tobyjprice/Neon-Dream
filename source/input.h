#pragma once
#include "SDL.h"
#include "Directions.h"

class Input
{
public:
	Input();
	~Input();
	int get_current_input();
	void process_input(SDL_Keycode * inKey);
private:
	int input;
};

