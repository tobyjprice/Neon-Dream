#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "game_state.h"
#include "menu.h"
#include <chrono>

static void process_input(bool* running, SDL_Window&, game_state* game);
static void update(game_state* game, double deltaTime, sprite* temp);
static void render(game_state& game, sprite* temp);

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
	game_state game(renderer);

	SDL_RenderSetLogicalSize(game.gameRenderer, 224, 278);
	
	game.load_new_game();

	sprite* tempSprite = new sprite(1, 1, game.spriteList[0]->xPos + game.spriteList[0]->xAnchor, game.spriteList[0]->yPos + game.spriteList[0]->yAnchor, SDL_LoadBMP("resources//test2.bmp"), game.gameRenderer);

	bool running = true;
	std::chrono::high_resolution_clock::time_point prevTime = std::chrono::high_resolution_clock::now();
	double acc = 0.0;
	double dt = 0.00025;
	double t = 0.0;

	while (running)
	{
		auto currTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currTime - prevTime);
		double frameTimeNano = deltaTime.count();
		double frameTimeSec = frameTimeNano / 1000000000;
		prevTime = currTime;

		acc += frameTimeSec;

		while (acc >= dt)
		{
			update(&game, dt, tempSprite);
			acc -= dt;
			t += dt;
		}

		process_input(&running, *window, &game);
		render(game, tempSprite);

		std::cout << 1 / frameTimeSec << std::endl;
		//std::cout << temp->xVel << " " << temp->yVel << " " << temp->direction << temp->yPos << std::endl;
	}

	return 0;
}

void process_input(bool* running, SDL_Window &window, game_state* game)
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
				game->pause_game();
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
		default:
			break;
		}
	}
}

void update(game_state* game, double deltaTime, sprite* temp)
{
	game->update(deltaTime);
}

void render(game_state& game, sprite* temp)
{
	SDL_SetRenderDrawColor(game.gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(game.gameRenderer);
	
	if (game.showSplash)
	{
		SDL_RenderCopy(game.gameRenderer, game.splashScreen->items[0]->texture, NULL, &game.splashScreen->items[0]->rect);
	}
	else if (game.showMainMenu)
	{
		for (auto& item : game.mainMenu->items)
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
	SDL_RenderCopy(game.gameRenderer, temp->getTexture(), NULL, &temp->getRect());
	SDL_RenderPresent(game.gameRenderer);
}