#include "sprite.h"

sprite::sprite(int w, int h, double x, double y, char* fileName, SDL_Renderer* renderer)
{
	width = w;
	height = h;
	xPos = x;
	yPos = y;
	direction = 0;

	left = xPos;
	right = yPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPos;
	rect.y = yPos;
	rect.h = height;
	rect.w = width;

	surface = SDL_LoadBMP(fileName);
	SDL_SetColorKey(surface, NULL, 0);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

sprite::sprite()
{

}

sprite::~sprite()
{
}

void sprite::update(double dt, sprite* collider)
{
	switch (direction)
	{
	case 0:
		xVel = 0;
		yVel = 0;
		break;
	case 1:
		xVel = 0;
		yVel = -1;
		break;
	case 2:
		xVel = -1;
		yVel = 0;
		break;
	case 3:
		xVel = 0;
		yVel = 1;
		break;
	case 4:
		xVel = 1;
		yVel = 0;
		break;
	default:
		break;
	}

	if (checkCollision(this, collider))
	{
		setVel(xVel, 0);
		direction = 5;
		//SDL_Log("Collision Detected");
	}

	xPos += xVel * 100 * dt;
	yPos += yVel * 100 * dt;

	left = xPos;
	right = yPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPos;
	rect.y = yPos;
}

bool sprite::checkCollision(sprite* one, sprite* two)
{
	if (one->bottom > two->top && one->top < two->bottom && one->right > two->left && one->left < two->right)
	{
		return true;
	}

	return false;
}


void sprite::setDir(int dir)
{
	direction = dir;
}

void sprite::setVel(double x, double y)
{
	xVel = x;
	yVel = y;
}

SDL_Texture* sprite::getTexture()
{
	return texture;
}

SDL_Rect sprite::getRect()
{
	return rect;
}

double sprite::getXPos()
{
	return xPos;
}