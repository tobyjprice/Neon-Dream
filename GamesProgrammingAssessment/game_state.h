#pragma once
#include <vector>
#include "sprite.h"
#include "ghost.h"
#include "mapPoint.h"
#include "menu.h"
#include "menu_main.h"
#include "options_menu.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "log_system.h"

class game_state
{
public:
	game_state(SDL_Window* window, SDL_Renderer *renderer);
	~game_state();
	void load_new_game();
	void load_resources();
	void load_map();
	void load_sprites();
	void populate_map();
	void update(double deltaTime);
	void playerDeath();
	void pause_game();
	void game_over();
	void game_won();
	void reset_sprites_pos();

	int playerScore;
	log_system* logSystem;
	int playerLives;
	bool running, gameActive, fullscreen, gameOver, gameWon;
	SDL_GameController* gameController;
	menu* pauseMenu;
	menu* splashScreen;
	menu_main* mainMenu;
	options_menu* optionsMenu;
	menu_item* gameOverText;
	menu_item* gameWonText;
	SDL_Surface* getWallSurface(int x, int y, int width);
	int getArrPos(int i, int j, int width);
	sprite* getSprite(int spriteId);
	bool game_state::checkCollision(sprite* one, sprite* two);
	sprite* player;
	std::vector<ghost*> ghostList;
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	std::vector<sprite*> pelletList;
	std::vector<sprite*> spriteList;
	std::vector<int> mapGrid;
	int mapWidth, mapHeight;
	int currTick, lastTick, gameStartTick, gameEndTick;
	int input, mainMenuOutput, optionsOutput;
private:
	Mix_Music* mainMusic;
	Mix_Music* gameMusic;
	Mix_Chunk* blipSfx;
	Mix_Chunk* powerupSfx;
	Mix_Chunk* powerupSfx2;
	Mix_Chunk* loseSfx;
	Mix_Chunk* gameOverSfx;
	bool mainMusicPlaying;
	int musicVolume;
	SDL_Surface* playerSurface;
	SDL_Surface* bottomLeft;
	SDL_Surface* bottomRight;
	SDL_Surface* topLeft;
	SDL_Surface* topRight;
	SDL_Surface* horiBottom;
	SDL_Surface* horiTop;
	SDL_Surface* vertLeft;
	SDL_Surface* vertRight;
	SDL_Surface* bottomRightInside;
	SDL_Surface* bottomLeftInside;
	SDL_Surface* topRightInside;
	SDL_Surface* topLeftInside;
	SDL_Surface* ghostWall;
	SDL_Surface* pellet;
	SDL_Surface* powerup;
	bool paused;
};

