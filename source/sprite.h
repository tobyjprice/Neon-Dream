#pragma once
#include "SDL.h"
#include <vector>
#include "SDL_Mixer.h"

class sprite
{
public:
	sprite();
	sprite(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Surface* inSurface2, SDL_Surface* inSurface3, SDL_Renderer* renderer, std::vector<int>* inMapGrid);
	~sprite();
	void set_sfx(Mix_Chunk* pelletDeathSfx);
	void animate();
	void get_input();
	SDL_Texture* getTexture();
	SDL_Rect getRect();
	double getXPos();
	Mix_Chunk* pelletDeath;
	virtual void update(double deltaTime, std::vector<sprite*>* pelletGrid, int tick, int* score);
	void set_velocity();
	void set_direction();
	void move(double deltaTime);
	void reset_sprite(int x, int y);
	int checkRight(std::vector<int>& mapGrid);
	int checkLeft(std::vector<int>& mapGrid);
	int checkUp(std::vector<int>& mapGrid);
	int checkDown(std::vector<int>& mapGrid);
	int boostVal;
	bool boostActive;
	void setInput(int input);
	void setVel(double x, double y);
	int getArrPos(int x, int y);
	int top, bottom, left, right;
	double xPos, yPos, xVel, yVel;
	int speed;
	int width, height, direction, xPosInt, yPosInt;
	int xGridPos, yGridPos, xAnchor, yAnchor;
	bool moveUp, moveDown, moveLeft, moveRight;
	SDL_Rect rect;
	int animFrame;
	std::vector<int>* mapGrid;

	int input;
protected:
	SDL_Surface* surface;
	SDL_Surface* surface2;
	SDL_Surface* surface3;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	void hitPellet(std::vector<sprite*>* pelletList, int* score);
};

