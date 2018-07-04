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
		SDL_Log("Input: UP");
		break;
	case SDLK_a:
		input = LEFT;
		SDL_Log("Input: LEFT");
		break;
	case SDLK_s:
		input = DOWN;
		SDL_Log("Input: DOWN");
		break;
	case SDLK_d:
		input = RIGHT;
		SDL_Log("Input: RIGHT");
		break;
	default:
		input = NULL;
		SDL_Log("Input: NULL");
		break;
	}

}
