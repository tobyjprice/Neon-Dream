#include <iostream>
#include "SDL.h"
#include "game_state.h"

static void process_input(bool *running, SDL_Window&);
static void update(game_state *game);
static void render(game_state *game);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	SDL_Window *window;
	SDL_Renderer *renderer;
	game_state game;

	SDL_CreateWindowAndRenderer(1600, 900, SDL_WINDOW_RESIZABLE, &window, &renderer);

	bool running = true;

	while (running)
	{
		process_input(&running, *window);
		update(&game);
		render(&game);
	}

	return 0;
}

void process_input(bool *running, SDL_Window &window)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				*running = false;
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			*running = false;
			break;
		default:
			break;
		}
	}

}

void update(game_state *game)
{

}

void render(game_state *game)
{

}