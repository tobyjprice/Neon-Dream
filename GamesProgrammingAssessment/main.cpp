#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "game_state.h"
#include "menu.h"
#include <chrono>

static void process_input(bool* running, SDL_Window&, game_state* game);
static void update(game_state* game, double deltaTime);
static void render(game_state& game);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	SDL_DisplayMode display;
	SDL_GetDesktopDisplayMode(0, &display);

	SDL_Window* window = SDL_CreateWindow("Toby Price - 13480955", display.w / 4, display.h / 4, display.w / 2, display.h / 2, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, NULL);
	game_state game(window, renderer);

	SDL_RenderSetLogicalSize(game.gameRenderer, 224, 278);
	
	//game.load_resources();

	game.running = true;
	std::chrono::high_resolution_clock::time_point prevTime = std::chrono::high_resolution_clock::now();
	double acc = 0.0;
	double dt = 0.00025;
	double t = 0.0;

	while (game.running)
	{
		auto currTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currTime - prevTime);
		double frameTimeNano = deltaTime.count();
		double frameTimeSec = frameTimeNano / 1000000000;
		prevTime = currTime;

		acc += frameTimeSec;

		while (acc >= dt)
		{
			update(&game, dt);
			acc -= dt;
			t += dt;
		}

		process_input(&game.running, *window, &game);
		render(game);

		//std::cout << 1 / frameTimeSec << std::endl;
		//std::cout << temp->xVel << " " << temp->yVel << " " << temp->direction << temp->yPos << std::endl;
	}

	return 0;
}

void process_input(bool* running, SDL_Window &window, game_state* game)
{
	SDL_Event event;

	if (SDL_NumJoysticks() < 1)
	{
		printf("NO JOYSTICK");
	}

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				SDL_Log("Key Esc pressed");
				game->input = 6;
				break;
			case SDLK_w:
				SDL_Log("Key w pressed");
				game->input = 1;
				break;
			case SDLK_a:
				SDL_Log("Key a pressed");
				game->input = 2;
				break;
			case SDLK_s:
				SDL_Log("Key s pressed");
				game->input = 3;
				break;
			case SDLK_d:
				SDL_Log("Key d pressed");
				game->input = 4;
				break;
			case SDLK_RETURN:
				SDL_Log("Key Enter pressed");
				game->input = 5;
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			*running = false;
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			switch (event.cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_DPAD_UP:
				SDL_Log("DPAD UP");
				game->input = 1;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				SDL_Log("DPAD LEFT");
				game->input = 2;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
				SDL_Log("DPAD DOWN");
				game->input = 3;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				SDL_Log("DPAD RIGHT");
				game->input = 4;
				break;
			case SDL_CONTROLLER_BUTTON_A:
				SDL_Log("A Button");
				game->input = 5;
				break;
			case SDL_CONTROLLER_BUTTON_START:
				SDL_Log("Start Button");
				game->input = 6;
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void update(game_state* game, double deltaTime)
{
	game->update(deltaTime);
}

void render(game_state& game)
{
	SDL_SetRenderDrawColor(game.gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(game.gameRenderer);
	
	if (game.splashScreen->active)
	{
		SDL_RenderCopy(game.gameRenderer, game.splashScreen->items[0]->texture, NULL, &game.splashScreen->items[0]->rect);
	}
	else if (game.mainMenu->active)
	{
		for (auto& item : game.mainMenu->items)
		{
			SDL_RenderCopy(game.gameRenderer, item->texture, NULL, &item->rect);
		}
		
	}
	else if (game.optionsMenu->active)
	{
		for (auto& item : game.optionsMenu->items)
		{
			SDL_RenderCopy(game.gameRenderer, item->texture, NULL, &item->rect);
		}
	}
	else 
	{
		for (auto& sprite : game.spriteList)
		{
			SDL_RenderCopy(game.gameRenderer, sprite->getTexture(), NULL, &sprite->getRect());
		}
		if (game.pauseMenu->items.size() > 0 && game.pauseMenu->active == true)
		{
			for (auto& menuItem : game.pauseMenu->items)
			{
				SDL_RenderCopy(game.gameRenderer, menuItem->texture, NULL, &menuItem->rect);
			}
		}
	}
	if (game.gameOver)
	{
		SDL_RenderCopy(game.gameRenderer, game.gameOverText->texture, NULL, &game.gameOverText->rect);
	}
	SDL_RenderPresent(game.gameRenderer);
}