#pragma once
#include "SDL.h"
#include "Directions.h"

class Input
{
public:
	Input();
	~Input();
	void process_input(SDL_Keycode * inKey);
	
	int input;
};

