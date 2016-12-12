#pragma once
#include "SDL.h"

class sprite
{
public:
	sprite();
	sprite(int w, int h, double x, double y, char*, SDL_Renderer* renderer);
	~sprite();
	SDL_Texture* getTexture();
	SDL_Rect getRect();
	double getXPos();
	void update(double deltaTime, sprite* collider);
	bool checkCollision(sprite* one, sprite* two);
	void setDir(int dir);
	void setVel(double x, double y);
	int top, bottom, left, right;
	double xPos, yPos, xVel, yVel;
	int width, height, direction;
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};

