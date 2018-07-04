#include "input.h"

Input::Input()
{
}


Input::~Input()
{
}

void Input::process_input(SDL_Keycode* inKey)
{
	switch (*inKey)
	{
	case SDLK_w:
		input = UP;
		break;
	case SDLK_a:
		input = LEFT;
		break;
	case SDLK_s:
		input = DOWN;
		break;
	case SDLK_d:
		input = RIGHT;
		break;
	default:
		break;
	}

}
