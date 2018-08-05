#include "game_state.h"
#include "SDL_image.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "menu.h"
#include "menu_main.h"
#include "options_menu.h"
#include "SDL_mixer.h"

game_state::game_state(SDL_Window* window, SDL_Renderer *renderer, Input* inputM)
{
	if (TTF_Init() != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init Error: %s\n", SDL_GetError());
	}
	SDL_Log("SDL_ttf initialised OK!\n");
	debugActive = false;
	logSystem = new log_system(renderer);
	gameRenderer = renderer;
	gameWindow = window;
	fullscreen = false;
	mapGrid.reserve(28 * 31);
	pelletList.reserve(28 * 31);
	for (int x = 0; x < 28 * 31; x++)
	{
		pelletList.push_back(NULL);
	}
	mapWidth = 28;
	mapHeight = 31;

	pauseMenu = new menu(gameRenderer);
	splashScreen = new menu_item("NEON DREAM", 50, 120, 120, 40, gameRenderer);
	mainMenu = new menu_main(gameRenderer);
	optionsMenu = new options_menu(gameRenderer);
	gameOverText = new menu_item("Game Over", 60, 105, 100, 20, gameRenderer);
	gameWonText = new menu_item("Game Won", 60, 105, 100, 20, gameRenderer);
	splashScreenActive = true;
	mainMenu->active = false;
	optionsMenu->active = false;
	gameActive = false;
	mainMenuOutput = -1;
	optionsOutput = -1;
	musicVolume = 20;
	gameOver = false;
	gameWon = false;

	inputManager = inputM;

	std::string volString = "Music Volume - ";
	volString.append(std::to_string(musicVolume));

	char* str = new char[volString.length() + 1];
	std::strcpy(str, volString.c_str());

	optionsMenu->items[1]->set_text(str);

	load_resources();

	// Initialises the gamepad/joystick, checks to see that at least one is connected
	if (SDL_NumJoysticks() < 1)
	{
		logSystem->addLog("No Controller Found", 1);
	}
	else
	{
		gameController = SDL_GameControllerOpen(0);
		if (gameController == NULL)
		{
			logSystem->addLog("Game Controller: Not initialised", 1);
		}
		else
		{
			logSystem->addLog("GameController: Initialised", 2);
		}

	}

	logSystem->addLog("Game State Initialised", 2);
}


game_state::~game_state()
{
}

void game_state::load_new_game()
{
	logSystem->addLog("New Game Loading", 2);
	gameEndTick = -1;
	gameStartTick = SDL_GetTicks();
	gameActive = false;
	playerLives = 3;
	paused = true;
	playerScore = 0;
	spriteList.clear();
	ghostList.clear();
	load_map();
	populate_map();
	load_sprites();
	Mix_HaltMusic();
	Mix_PlayMusic(gameMusic, -1);
}

void game_state::load_resources()
{
	// Images
	playerSurface = IMG_Load("resources//player//player.png");
	playerSurface2 = IMG_Load("resources//player//player2.png");
	playerSurface3 = IMG_Load("resources//player//player3.png");
	bottomLeft = IMG_Load("resources//Bottom-Left-Corner.png");
	bottomRight = IMG_Load("resources//Bottom-Right-Corner.png");
	topLeft = IMG_Load("resources//Top-Left-Corner.png");
	topRight = IMG_Load("resources//Top-Right-Corner.png");
	horiBottom = IMG_Load("resources//Bottom-Horizontal.png");
	horiTop = IMG_Load("resources//Top-Horizontal.png");
	vertLeft = IMG_Load("resources//Left-Vertical.png");
	vertRight = IMG_Load("resources//Right-Vertical.png");
	bottomRightInside = IMG_Load("resources//Bottom-Right-Corner-Inside.png");
	bottomLeftInside = IMG_Load("resources//Bottom-Left-Corner-Inside.png");
	topRightInside = IMG_Load("resources//Top-Right-Corner-Inside.png");
	topLeftInside = IMG_Load("resources//Top-Left-Corner-Inside.png");
	ghostWall = IMG_Load("resources//Ghost-Wall.png");
	pellet = IMG_Load("resources//Pellet.png");
	powerup = IMG_Load("resources//powerup.png");
	ghostASurface = IMG_Load("resources//ninja//blue0.png");
	ghostASurface2 = IMG_Load("resources//ninja//blue1.png");
	ghostASurface3 = IMG_Load("resources//ninja//blue2.png");
	ghostBSurface = IMG_Load("resources//ninja//green0.png");
	ghostBSurface2 = IMG_Load("resources//ninja//green1.png");
	ghostBSurface3 = IMG_Load("resources//ninja//green2.png");
	ghostCSurface = IMG_Load("resources//ninja//red0.png");
	ghostCSurface2 = IMG_Load("resources//ninja//red1.png");
	ghostCSurface3 = IMG_Load("resources//ninja//red2.png");
	ghostDSurface = IMG_Load("resources//ninja//yellow0.png");
	ghostDSurface2 = IMG_Load("resources//ninja//yellow1.png");
	ghostDSurface3 = IMG_Load("resources//ninja//yellow2.png");


	// Sounds
	//Initialise SDL_mixer
	if (Mix_OpenAudio(11025, MIX_DEFAULT_FORMAT, 2, 512) == -1)
	{
		logSystem->addLog("SDL_Mixer: Failed to Initialise", 0);
	}

	mainMusic = Mix_LoadMUS("resources//Sounds//DieHistoric.wav");
	gameMusic = Mix_LoadMUS("resources//Sounds//HotNights.wav");
	Mix_VolumeMusic(musicVolume);
	mainMusicPlaying = false;

	blipSfx = Mix_LoadWAV("resources//Sounds//blip.wav");
	powerupSfx = Mix_LoadWAV("resources//Sounds//powerup.wav");
	powerupSfx2 = Mix_LoadWAV("resources//Sounds//powerup2.wav");
	loseSfx = Mix_LoadWAV("resources//Sounds//lose.wav");
	gameOverSfx = Mix_LoadWAV("resources//Sounds//gameover.wav");

	if (mainMusic != NULL || gameMusic != NULL || blipSfx != NULL || powerupSfx != NULL || powerupSfx2 != NULL || loseSfx != NULL || gameOverSfx != NULL)
	{
		logSystem->addLog("Sound: Loaded", 2);
	}
	else
	{
		logSystem->addLog("Sound: Load Failed", 0);
	}
}

void game_state::load_map()
{
	std::ifstream file;
	std::string fileName = "map.txt";
	std::string temp;

	int elmNum = 0;
	int numCount = 0;
	int rowCount = 0;

	file.open("resources//" + fileName, std::ios::in);

	while (getline(file, temp, ','))
	{
		mapGrid.push_back(std::stoi(temp));
	}

	file.close();
}

void game_state::populate_map()
{
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			int pointType = mapGrid[getArrPos(x, y, mapWidth)];

			sprite* tempSprite;
			switch (pointType)
			{
			case 0: // Blank space
				break;
			case 1: // Wall
				tempSprite = new sprite(8, 8, x * 8, y * 8, getWallSurface(x, y, mapWidth), getWallSurface(x, y, mapWidth), getWallSurface(x, y, mapWidth), gameRenderer, &mapGrid);
				spriteList.push_back(tempSprite);
				break;
			case 2: // Pellet
				tempSprite = new sprite(2, 2, (x * 8) + 3, (y * 8) + 3, pellet, pellet, pellet, gameRenderer, &mapGrid);
				pelletList[getArrPos(x, y, 28)] = tempSprite;
				break;
			case 3: // Power up
				tempSprite = new sprite(4, 4, (x * 8) + 2, (y * 8) + 2, powerup, powerup, powerup, gameRenderer, &mapGrid);
				pelletList[getArrPos(x, y, 28)] = tempSprite;
				break;
			case 4: // Ghost Gate
				tempSprite = new sprite(8, 8, x * 8, y * 8, ghostWall, ghostWall, ghostWall, gameRenderer, &mapGrid);
				spriteList.push_back(tempSprite);
				break;
			default:
				break;
			}
		}
	}
	logSystem->addLog("Map Loaded", 2);
}

void game_state::load_sprites()
{
	// Fill player var with new Player temp.
	Player* tempPlr = new Player(12, 12, 108, 184, playerSurface, playerSurface2, playerSurface3, gameRenderer, &mapGrid, inputManager);

	tempPlr->xGridPos = 5;
	tempPlr->yGridPos = 5;

	player = tempPlr;
	player->set_sfx(blipSfx);

	for (int x = 0; x < 4; x++)
	{
		ghost* tempGhost;
		switch (x)
		{
		case 0:
			tempGhost = new ghost(12, 12, 108, 88, ghostASurface, ghostASurface2, ghostASurface3, gameRenderer);
			ghostList.emplace_back(tempGhost);
			break;
		case 1:
			tempGhost = new ghost(12, 12, 108, 88, ghostBSurface, ghostBSurface2, ghostBSurface3, gameRenderer);
			ghostList.emplace_back(tempGhost);
			break;
		case 2:
			tempGhost = new ghost(12, 12, 108, 88, ghostCSurface, ghostCSurface2, ghostCSurface3, gameRenderer);
			ghostList.emplace_back(tempGhost);
			break;
		case 3:
			tempGhost = new ghost(12, 12, 108, 88, ghostDSurface, ghostDSurface2, ghostDSurface3, gameRenderer);
			ghostList.emplace_back(tempGhost);
			break;
		default:
			break;
		}
	}

	if (player == NULL || spriteList.size() < 1 || ghostList.size() < 1)
	{
		logSystem->addLog("Sprites Not Loaded", 0);
	}
	else
	{
		logSystem->addLog("Sprites Loaded", 2);
	}

	lastTick = 0;
}

SDL_Surface* game_state::getWallSurface(int x, int y, int width)
{
	SDL_Surface* tempSurface;
	int rightObj = 0;
	int leftObj = 0;
	int upObj = 0;
	int downObj = 0;
	int upLeftObj = 1;
	int upRightObj = 1;
	int downLeftObj = 1;
	int downRightObj = 1;

	if (x == 0)
	{
		upObj = 1;
		downObj = 1;
		leftObj = 1;
		rightObj = mapGrid[getArrPos(x + 1, y, width)];
		if (y != 0) upRightObj = mapGrid[getArrPos(x + 1, y - 1, width)];
		if (y != 30) downRightObj = mapGrid[getArrPos(x + 1, y + 1, width)];
	}
	else if (x == 27)
	{
		upObj = 1;
		downObj = 1;
		rightObj = 1;
		leftObj = mapGrid[getArrPos(x - 1, y, width)];
		if (y != 0)	upLeftObj = mapGrid[getArrPos(x - 1, y - 1, width)];
		if (y != 30) downLeftObj = mapGrid[getArrPos(x - 1, y + 1, width)];
	}
	else if (y == 0)
	{
		upObj = 1;
		rightObj = 1;
		leftObj = 1;
		downObj = mapGrid[getArrPos(x, y + 1, width)];
		downLeftObj = mapGrid[getArrPos(x - 1, y + 1, width)];
		downRightObj = mapGrid[getArrPos(x + 1, y + 1, width)];
	}
	else if (y == 30)
	{
		downObj = 1;
		rightObj = 1;
		leftObj = 1;
		upObj = mapGrid[getArrPos(x, y - 1, width)];
		upLeftObj = mapGrid[getArrPos(x - 1, y - 1, width)];
		upRightObj = mapGrid[getArrPos(x + 1, y - 1, width)];
	}
	else
	{
		rightObj = mapGrid[getArrPos(x + 1, y, width)];
		leftObj = mapGrid[getArrPos(x - 1, y, width)];
		upObj = mapGrid[getArrPos(x, y - 1, width)];
		downObj = mapGrid[getArrPos(x, y + 1, width)];
		upLeftObj = mapGrid[getArrPos(x - 1, y - 1, width)];
		upRightObj = mapGrid[getArrPos(x + 1, y - 1, width)];
		downLeftObj = mapGrid[getArrPos(x - 1, y + 1, width)];
		downRightObj = mapGrid[getArrPos(x + 1, y + 1, width)];
	}


	if ((rightObj == 1) && (leftObj == 1) && (upObj == 1) && (downObj == 1))
	{
		if (downLeftObj != 1)
		{
			tempSurface = topRightInside;
		}
		else if (upLeftObj != 1)
		{
			tempSurface = bottomRightInside;
		}
		else if (downRightObj != 1)
		{
			tempSurface = topLeftInside;
		}
		else if (upRightObj != 1)
		{
			tempSurface = bottomLeftInside;
		}
		else
		{
			tempSurface = NULL;
		}
	}
	else if ((downObj == 1 || downObj == 10) && (leftObj == 1 || leftObj == 10) && (rightObj == 1 || rightObj == 10))
	{
		tempSurface = horiTop;
	}
	else if ((downObj == 1 || downObj == 10) && (leftObj == 1 || leftObj == 10) && (upObj == 1 || upObj == 10))
	{
		tempSurface = vertRight;
	}
	else if ((rightObj == 1 || rightObj == 10) && (downObj == 1 || downObj == 10) && (upObj == 1 || upObj == 10))
	{
		tempSurface = vertLeft;
	}
	else if ((rightObj == 1 || rightObj == 10) && (leftObj == 1 || leftObj == 10) && (upObj == 1 || upObj == 10))
	{
		tempSurface = horiBottom;
	}
	else if ((downObj == 1 || downObj == 10) && (rightObj == 1 || rightObj == 10))
	{
		tempSurface = topLeft;
	}
	else if ((downObj == 1 || downObj == 10) && (leftObj == 1 || leftObj == 10))
	{
		tempSurface = topRight;
	}
	else if ((upObj == 1 || upObj == 10) && (rightObj == 1 || rightObj == 10))
	{
		tempSurface = bottomLeft;
	}
	else if ((upObj == 1 || upObj == 10) && (leftObj == 1 || leftObj == 10))
	{
		tempSurface = bottomRight;
	}
	else if (upObj == 0 && downObj == 5 && (rightObj == 1 || rightObj == 4) && (leftObj == 4 || leftObj == 1))
	{
		tempSurface = horiTop;
	}
	else if (upObj == 5 && downObj == 0 && (rightObj == 1 || rightObj == 4) && (leftObj == 4 || leftObj == 1))
	{
		tempSurface = horiBottom;
	}
	else if (upObj == 1 && downObj == 1 && rightObj == 0 && leftObj == 5)
	{
		tempSurface = vertRight;
	}
	else if (upObj == 1 && downObj == 1 && rightObj == 5 && leftObj == 0)
	{
		tempSurface = vertLeft;
	}
	else
	{
		tempSurface = NULL;
	}

	return tempSurface;
}

void game_state::update(double dt)
{
	currTick = SDL_GetTicks();
	if (currTick > 3200 && !mainMusicPlaying)
	{
		Mix_PlayMusic(mainMusic, -1);
		mainMusicPlaying = true;
	}
	else if (currTick > 4000 && splashScreenActive)
	{
		splashScreenActive = false;
		mainMenu->active = true;
	}
	
	if (mainMenu->active)
	{
		mainMenu->update(input, &mainMenuOutput);
		input = 0;
	}
	else if (optionsMenu->active)
	{
		optionsMenu->update(input, &optionsOutput);
		if (input == 6)
		{
			optionsMenu->active = false;
			mainMenu->active = true;
			mainMenuOutput = -1;
		}
		input = 0;
	}
	else if (input == 6 && !splashScreenActive)
	{
		pause_game();
		input = 0;
	}
	
	if (gameStartTick > 0 && currTick - gameStartTick > 3000 && !gameActive)
	{
		paused = false;
		gameActive = true;
	}
	// Game over screen
	if (gameEndTick > 0 && currTick - gameEndTick > 3000)
	{
		mainMenu->active = true;
		mainMenu->selItem = 0;
		ghostList.clear();
		spriteList.clear();
		Mix_PlayMusic(mainMusic, -1);
		gameEndTick = -1;
		input = 0;
		gameOver = false;
		gameWon = false;
		playerScore = 0;
		logSystem->showScore(playerScore);
	}
	else if (!paused)
	{
		int tempScore = playerScore;
		player->update(dt, &pelletList, currTick, &playerScore);
		if (playerScore != tempScore)
		{
			logSystem->showScore(playerScore);
		}
		if (playerScore == 24400)
		{
			game_won();
		}

		for (auto& elem : ghostList)
		{
			//elem->update(dt, &mapGrid, currTick);

			if (checkCollision(player, elem))
			{
				logSystem->addLog("Player Death", 4);
				playerDeath();
				break;
			}
		}
	}
	switch (mainMenuOutput)
	{
	case 0:
		logSystem->addLog("Main Menu Closed", 4);
		mainMenu->active = false;
		load_new_game();
		mainMenuOutput = -1;
		break;
	case 1:
		// Show options menu
		logSystem->addLog("Options Menu Opened", 4);
		mainMenu->active = false;
		optionsMenu->active = true;
		switch (optionsOutput)
		{
		case 0:
			if (!fullscreen) 
			{
				SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
				fullscreen = true;
				logSystem->addLog("Fullscreen On", 4);
				char* str = "Fullscreen - Active";
				optionsMenu->items[0]->set_text(str);
			}
			else
			{
				SDL_SetWindowFullscreen(gameWindow, 0);
				fullscreen = false;
				logSystem->addLog("Fullscreen Off", 4);
				char* str = "Fullscreen - Inactive";
				optionsMenu->items[0]->set_text(str);
			}
			break;
		case 1:
			if (musicVolume == 100)
			{
				musicVolume = 0;
				Mix_VolumeMusic(musicVolume);

				std::string volString = "Music Volume - ";
				volString.append(std::to_string(musicVolume));

				char* str = new char[volString.length() + 1];
				std::strcpy(str, volString.c_str());

				optionsMenu->items[1]->set_text(str);
			}
			else
			{
				musicVolume++;
				Mix_VolumeMusic(musicVolume);

				std::string volString = "Music Volume - ";
				volString.append(std::to_string(musicVolume));

				char* str = new char[volString.length() + 1];
				std::strcpy(str, volString.c_str());

				optionsMenu->items[1]->set_text(str);
			}
			break;
		case 2:
			optionsMenu->active = false;
			mainMenu->active = true;
			mainMenuOutput = -1;
			break;
		default:
			break;
		}
		optionsOutput = -1;
		break;
	case 2:
		running = false;
		break;
	default:
		break;
	}
	lastTick = currTick;
}

bool game_state::checkCollision(sprite* one, sprite* two)
{
	if (one->bottom > two->top && one->top < two->bottom && one->right > two->left && one->left < two->right)
	{
		return true;
		playerDeath();
	}
	else
	{
		return false;
	}
}

void game_state::playerDeath()
{
	if (playerLives > 1)
	{
		Mix_PlayChannel(-1, loseSfx, 0);
		Mix_PlayMusic(gameMusic, -1);
		paused = true;
		reset_sprites_pos();
		gameStartTick = SDL_GetTicks();
		gameActive = false;
	}
	else
	{
		Mix_PlayChannel(-1, loseSfx, 0);
		game_over();
	}
	playerLives--;
}

void game_state::game_over()
{
	logSystem->addLog("Game Over", 4);
	Mix_PlayChannel(-1, gameOverSfx, 0);
	paused = true;
	Mix_HaltMusic();
	gameEndTick = SDL_GetTicks();
	gameOver = true;
}

void game_state::game_won()
{
	logSystem->addLog("Game Won", 4);
	paused = true;
	Mix_HaltMusic();
	gameEndTick = SDL_GetTicks();
	gameWon = true;
}

void game_state::reset_sprites_pos()
{
	logSystem->addLog("Sprite Position Reset", 4);
	player->xPos = 108;
	player->yPos = 184;
	player->input = 0;
	player->direction = 0;

	player->xVel = 0;
	player->yVel = 0;

	player->xAnchor = 0;
	player->yAnchor = 0;

	player->xPosInt = player->xPos;
	player->yPosInt = player->yPos;

	player->rect.x = player->xPos;
	player->rect.y = player->yPos;
	player->rect.h = player->height;
	player->rect.w = player->width;

	player->xGridPos = player->xPos / 8;
	player->yGridPos = player->yPos / 8;

	for (auto& elem : ghostList)
	{
		elem->xPos = 108;
		elem->yPos = 88;
		elem->input = 0;
		elem->direction = 0;

		elem->xVel = 0;
		elem->yVel = 0;

		elem->xAnchor = 0;
		elem->yAnchor = 0;

		elem->xPosInt = elem->xPos;
		elem->yPosInt = elem->yPos;

		elem->rect.x = elem->xPos;
		elem->rect.y = elem->yPos;
		elem->rect.h = elem->height;
		elem->rect.w = elem->width;

		elem->xGridPos = elem->xPos / 8;
		elem->yGridPos = player->yPos / 8;
	}
}

void game_state::pause_game()
{
	if (!paused)
	{
		logSystem->addLog("Game Paused", 4);
		paused = true;
		pauseMenu->active = true;
		Mix_PauseMusic();
	}
	else
	{
		logSystem->addLog("Game Unpaused", 4);
		paused = false;
		pauseMenu->active = false;
		Mix_ResumeMusic();
	}
}

int game_state::getArrPos(int x, int y, int width)
{
	int k = (y * width) + x;

	return k;
}

sprite* game_state::getSprite(int spriteId)
{
	return spriteList[spriteId];
}

void game_state::check_plr_to_wall_collision()
{
	int xMapPos = player->xPos / 8;
	int yMapPos = player->yPos / 8;
	int moves[] = { 0,0,0,0 };


	// Check each direction
	// Up
	if (mapGrid[get_1D_array_pos(xMapPos, yMapPos - 1)] == 4 || mapGrid[get_1D_array_pos(xMapPos, yMapPos - 1)] == 1)
	{
		moves[0] = 1;
	}

	// Down
	if (mapGrid[get_1D_array_pos(xMapPos, yMapPos + 1)] == 4 || mapGrid[get_1D_array_pos(xMapPos, yMapPos + 1)] == 1)
	{
		moves[1] = 1;
	}

	// Left
	if (mapGrid[get_1D_array_pos(xMapPos - 1, yMapPos)] == 4 || mapGrid[get_1D_array_pos(xMapPos - 1, yMapPos)] == 1)
	{
		moves[2] = 1;
	}

	// Right
	if (mapGrid[get_1D_array_pos(xMapPos + 1, yMapPos)] == 4 || mapGrid[get_1D_array_pos(xMapPos + 1, yMapPos)] == 1)
	{
		moves[3] = 1;
	}

	//player->set_pot_moves(moves);
}

int game_state::get_1D_array_pos(int x, int y)
{
	int k = (y * mapWidth) + x;

	return k;
}

