#include "sprite.h"
#include <iostream>
//#include <vector>

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

	xGridPos = xPos / 8;
	yGridPos = yPos / 8;

	surface = SDL_LoadBMP(fileName);
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
			xVel = 0;
			yVel = -1;
			yAnchor = 7;
			direction = 1;
		}
		else
		{
			yVel = 0;
		}
		
		//xAnchor = 0;
		break;
	case 2:
		if (checkLeft(mapGrid))
		{
			xVel = -1;
			yVel = 0;
			xAnchor = 7;
			direction = 2;
		}
		else
		{
			xVel = 0;
		}
		
		//yAnchor = 0;
		break;
	case 3:
		if (checkDown(mapGrid))
		{
			xVel = 0;
			yVel = 1;
			yAnchor = 0;
			direction = 3;
		}
		else
		{
			yVel = 0;
		}
		
		//xAnchor = 0;
		break;
	case 4:
		if (checkRight(mapGrid))
		{
			xVel = 1;
			yVel = 0;
			xAnchor = 0;
			direction = 4;
		}
		else
		{
			xVel = 0;
		}
		
		//yAnchor = 0;
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

	std::cout << xAnchor << " " << yAnchor << std::endl;

	xPos += xVel * 80 * dt;
	yPos += yVel * 80 * dt;

	xGridPos = (xPos + xAnchor) / 8;
	yGridPos = (yPos + yAnchor) / 8;

	left = xPos;
	right = yPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPos;
	rect.y = yPos;

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