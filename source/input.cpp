#include "input.h"

Input::Input()
{
}


Input::~Input()
{
}

int Input::get_current_input()
{
	return input;
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
	case SDLK_RETURN:
		input = SELECT;
		SDL_Log("Input: SELECT");
		break;
	default:
		input = NULL;
		SDL_Log("Input: NULL");
		break;
	}

}
