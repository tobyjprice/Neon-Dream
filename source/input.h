#pragma once
#include "SDL.h"

class input
{
public:
	input();
	~input();
	void process_input(SDL_Keycode * inKey);

};

