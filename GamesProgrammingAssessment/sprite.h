#pragma once
#include "SDL.h"
#include <vector>

class sprite
{
public:
	sprite();
	sprite(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Renderer* renderer);
	~sprite();
	SDL_Texture* getTexture();
	SDL_Rect getRect();
	double getXPos();
	virtual void update(double deltaTime, sprite* collider, std::vector<int>* mapGrid);
	void move(double deltaTime);
	bool checkCollision(sprite* one, sprite* two);
	int checkRight(std::vector<int>& mapGrid);
	int checkLeft(std::vector<int>& mapGrid);
	int checkUp(std::vector<int>& mapGrid);
	int checkDown(std::vector<int>& mapGrid);
	void setInput(int input);
	void setVel(double x, double y);
	int getArrPos(int x, int y);
	int top, bottom, left, right;
	double xPos, yPos, xVel, yVel;
	int width, height, direction, input, xPosInt, yPosInt;
	int xGridPos, yGridPos, xAnchor, yAnchor;
	bool moveUp, moveDown, moveLeft, moveRight;
	SDL_Rect rect;
protected:
	SDL_Surface* surface;
	SDL_Texture* texture;
	
};

