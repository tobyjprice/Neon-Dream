#include "sprite.h"
#include <iostream>
//#include <vector>

sprite::sprite(int w, int h, double x, double y, SDL_Surface* inSurface, SDL_Surface* inSurface2, SDL_Surface* inSurface3, SDL_Renderer* inRenderer)
{
	speed = 80;
	boostVal = 20;
	boostActive = false;
	animFrame = 0;
	renderer = inRenderer;
	width = w;
	height = h;
	xPos = x;
	yPos = y;
	direction = 0;

	xVel = 0;
	yVel = 0;

	xAnchor = 0;
	yAnchor = 0;

	xPosInt = xPos;
	yPosInt = yPos;

	left = xPos;
	right = yPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPosInt;
	rect.y = yPosInt;
	rect.h = height;
	rect.w = width;

	xGridPos = xPos / 8;
	yGridPos = yPos / 8;

	surface = inSurface;
	surface2 = inSurface2;
	surface3 = inSurface3;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

sprite::sprite()
{

}

sprite::~sprite()
{
}

void sprite::set_sfx(Mix_Chunk* pelletDeathSfx)
{
	pelletDeath = pelletDeathSfx;
}

void sprite::update(double dt, std::vector<int>* mapGrid, std::vector<sprite*>* pelletGrid, int tick, int input, int* score)
{
	switch (input)
	{
	case 1:
		if (checkUp(*mapGrid) != 1 && checkUp(*mapGrid) != 4)
		{
			if (xPosInt >= xGridPos * 8 && xPosInt + 8 <= (xGridPos * 8) + 8)
			{
				direction = input;
			}
		}
		break;
	case 2:
		if (checkLeft(*mapGrid) != 1 && checkLeft(*mapGrid) != 4)
		{
			if (yPosInt >= yGridPos * 8 && yPosInt + 8 <= (yGridPos * 8) + 8)
			{
				direction = input;
			}
		}
		break;
	case 3:
		if (checkDown(*mapGrid) != 1 && checkDown(*mapGrid) != 4)
		{
			if (xPosInt >= xGridPos * 8 && xPosInt + 8 <= (xGridPos * 8) + 8)
			{
				direction = input;
			}
		}
		break;
	case 4:
		if (checkRight(*mapGrid) != 1 && checkRight(*mapGrid) != 4)
		{
			if (yPosInt >= yGridPos * 8 && yPosInt + 8 <= (yGridPos * 8) + 8)
			{
				direction = input;
			}
			
		}
		break;
	case 5:
		if (speed == 80)
		{
			speed = 160;
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
		if (checkUp(*mapGrid) != 1 && checkUp(*mapGrid) != 4)
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
		if (checkLeft(*mapGrid) != 1 && checkLeft(*mapGrid) != 4)
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
		if (checkDown(*mapGrid) != 1 && checkDown(*mapGrid) != 4)
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
		if (checkRight(*mapGrid) != 1 && checkRight(*mapGrid) != 4)
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

	hitPellet(pelletGrid, score);

	//std::cout << xAnchor << " " << yAnchor << std::endl;
	//std::cout << xGridPos << " " << yGridPos << std::endl;

	move(dt);

	//std::cout << "   " << mapGrid[getArrPos(yGridPos, xGridPos - 1)] << std::endl;
	//std::cout << mapGrid[getArrPos(yGridPos - 1, yGridPos)] << " " << yGridPos << " " << xGridPos << " " << mapGrid[getArrPos(yGridPos + 1, xGridPos)] << std::endl;
	//std::cout << "   " << mapGrid[getArrPos(yGridPos, xGridPos + 1)] << std::endl << std::endl;
}

void sprite::move(double dt)
{
	xPos += xVel * speed * dt;
	yPos += yVel * speed * dt;

	xPosInt = xPos;
	yPosInt = yPos;

	int xGridPosTemp = xGridPos;
	int yGridPosTemp = yGridPos;

	xGridPos = (xPos + xAnchor) / 8;
	yGridPos = (yPos + yAnchor) / 8;

	if (xGridPos != xGridPosTemp)
	{
		if (speed > 80)
		{
			speed -= 10;
		}
		
		animFrame++;
		animate();
	}
	else if (yGridPos != yGridPosTemp)
	{
		if (speed > 80)
		{
			speed -= 10;
		}
		animFrame = 0;
		animate();
	}

	left = xPos;
	right = xPos + width;
	top = yPos;
	bottom = yPos + height;

	rect.x = xPosInt - 2;
	rect.y = yPosInt - 2;
}

void sprite::animate()
{
	if (animFrame == 0)
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	else if (animFrame == 1)
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface2);
	}
	else if (animFrame == 2)
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface3);
	}
	else if (animFrame == 3)
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface2);
		
	}
	else if (animFrame == 4)
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		animFrame = 0;
	}
}

void sprite::reset_sprite(int x, int y)
{
	xPos = x;
	yPos = y;
	input = 0;
	direction = 0;

	xVel = 0;
	yVel = 0;

	xAnchor = 0;
	yAnchor = 0;

	xPosInt = xPos;
	yPosInt = yPos;

	rect.x = xPos;
	rect.y = yPos;
	rect.h = height;
	rect.w = width;

	xGridPos = xPos / 8;
	yGridPos = yPos / 8;
}

int sprite::checkRight(std::vector<int>& mapGrid)
{
	return mapGrid[getArrPos(xGridPos + 1, yGridPos)];
}

int sprite::checkLeft(std::vector<int>& mapGrid)
{
	return mapGrid[getArrPos(xGridPos - 1, yGridPos)];
}

int sprite::checkUp(std::vector<int>& mapGrid)
{
	return mapGrid[getArrPos(xGridPos, yGridPos - 1)];
}

int sprite::checkDown(std::vector<int>& mapGrid)
{
	return mapGrid[getArrPos(xGridPos, yGridPos + 1)];
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

void sprite::hitPellet(std::vector<sprite*>* pelletList, int* score)
{
	if (pelletList->at(getArrPos(xGridPos, yGridPos)) != NULL)
	{
		*score += 100;
		pelletList->at(getArrPos(xGridPos,yGridPos)) = NULL;
		Mix_PlayChannel(-1, pelletDeath, 0);
	}
}