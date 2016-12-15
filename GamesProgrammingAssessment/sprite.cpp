#include "sprite.h"
#include <iostream>
//#include <vector>

sprite::sprite(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Renderer* renderer)
{
	width = w;
	height = h;
	xPos = x;
	yPos = y;
	direction = 0;

	xPosInt = xPos;
	yPosInt = yPos;

	left = xPos;
	right = yPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPos;
	rect.y = yPos;
	rect.h = height;
	rect.w = width;

	xGridPos = xPos / 8;
	yGridPos = yPos / 8;

	surface = inSurface;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

sprite::sprite()
{

}

sprite::~sprite()
{
}

void sprite::update(double dt, sprite* collider, std::vector<int>& mapGrid)
{
	switch (input)
	{
	case 1:
		if (checkUp(mapGrid))
		{
			direction = input;
		}
		break;
	case 2:
		if (checkLeft(mapGrid))
		{
			direction = input;
		}
		break;
	case 3:
		if (checkDown(mapGrid))
		{
			direction = input;
		}
		break;
	case 4:
		if (checkRight(mapGrid))
		{
			direction = input;
		}
		break;
	default:
		break;
	}

	switch (direction)
	{
	case 0:
		xVel = 0;
		yVel = 0;
		xAnchor = 0;
		yAnchor = 0;
		break;
	case 1:
		if (checkUp(mapGrid))
		{
			if (xPosInt >= xGridPos * 8 && xPosInt + 8 <= (xGridPos * 8) + 8)
			{
				xVel = 0;
				yVel = -1;
				yAnchor = 7;
			}
		}
		else
		{
			yVel = 0;
		}
		break;
	case 2:
		if (checkLeft(mapGrid))
		{
			if (yPosInt >= yGridPos * 8 && yPosInt + 8 <= (yGridPos * 8) + 8)
			{
				xVel = -1;
				yVel = 0;
				xAnchor = 7;
			}
		}
		else
		{
			xVel = 0;
		}
		break;
	case 3:
		if (checkDown(mapGrid))
		{
			if (xPosInt >= xGridPos * 8 && xPosInt + 8 <= (xGridPos * 8) + 8)
			{
				xVel = 0;
				yVel = 1;
				yAnchor = 0;
			}
		}
		else
		{
			yVel = 0;
		}
		break;
	case 4:
		if (checkRight(mapGrid))
		{
			if (yPosInt >= yGridPos * 8 && yPosInt + 8 <= (yGridPos * 8) + 8)
			{
				xVel = 1;
				yVel = 0;
				xAnchor = 0;
			}
		}
		else
		{
			xVel = 0;
		}
		break;
	default:
		xVel = 0;
		yVel = 0;
		xAnchor = 0;
		yAnchor = 0;
		break;
	}

	if (checkCollision(this, collider))
	{
		setVel(xVel, 0);
		direction = 5;
		//SDL_Log("Collision Detected");
	}

	//std::cout << xAnchor << " " << yAnchor << std::endl;
	//std::cout << xGridPos << " " << yGridPos << std::endl;

	xPos += xVel * 80 * dt;
	yPos += yVel * 80 * dt;

	xPosInt = xPos;
	yPosInt = yPos;

	xGridPos = (xPos + xAnchor) / 8;
	yGridPos = (yPos + yAnchor) / 8;

	left = xPos;
	right = yPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPosInt - 2;
	rect.y = yPosInt - 2;

	//std::cout << "   " << mapGrid[getArrPos(yGridPos, xGridPos - 1)] << std::endl;
	//std::cout << mapGrid[getArrPos(yGridPos - 1, yGridPos)] << " " << yGridPos << " " << xGridPos << " " << mapGrid[getArrPos(yGridPos + 1, xGridPos)] << std::endl;
	//std::cout << "   " << mapGrid[getArrPos(yGridPos, xGridPos + 1)] << std::endl << std::endl;
}

bool sprite::checkCollision(sprite* one, sprite* two)
{
	if (one->bottom > two->top && one->top < two->bottom && one->right > two->left && one->left < two->right)
	{
		return true;
	}

	return false;
}

bool sprite::checkRight(std::vector<int>& mapGrid)
{
	if (mapGrid[getArrPos(xGridPos + 1, yGridPos)] == 1 || mapGrid[getArrPos(xGridPos + 1, yGridPos)] == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool sprite::checkLeft(std::vector<int>& mapGrid)
{
	if (mapGrid[getArrPos(xGridPos - 1, yGridPos)] == 1 || mapGrid[getArrPos(xGridPos - 1, yGridPos)] == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool sprite::checkUp(std::vector<int>& mapGrid)
{
	if (mapGrid[getArrPos(xGridPos, yGridPos - 1)] == 1 || mapGrid[getArrPos(xGridPos, yGridPos - 1)] == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool sprite::checkDown(std::vector<int>& mapGrid)
{
	if (mapGrid[getArrPos(xGridPos, yGridPos + 1)] == 1 || mapGrid[getArrPos(xGridPos, yGridPos + 1)] == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int sprite::getArrPos(int x, int y)
{
	int k = (y * 28) + x;

	return k;
}

void sprite::setInput(int in)
{
	input = in;
}

void sprite::setVel(double x, double y)
{
	xVel = x;
	yVel = y;
}

void sprite::setColorKey()
{
	if (surface != NULL)
	{
		SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 255, 255, 255));

	}
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