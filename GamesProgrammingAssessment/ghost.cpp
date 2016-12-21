#include "ghost.h"



ghost::ghost()
{

}

ghost::ghost(int w, int h, int x, int y, SDL_Surface* inSurface, SDL_Renderer* renderer)
{
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

	rect.x = xPos;
	rect.y = yPos;
	rect.h = height;
	rect.w = width;

	xGridPos = xPos / 8;
	yGridPos = yPos / 8;

	surface = inSurface;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void ghost::update(double dt, sprite* collider, std::vector<int>* mapGrid, int tick)
{
	if (tick % (rand() % 500 + 300) == 0)
	{
		int tempR = rand() % 4 + 1;
		if (tempR != 1 && input != 3 && input !=1)
		{
			input = tempR;
		}
		else if(tempR != 2 && input != 4 && input != 2)
		{
			input = tempR;
		} else if (tempR != 3 && input != 1 && input != 3)
		{
			input = tempR;
		}
		else if(tempR != 4 && input != 1 && input != 4)
		{
			input = tempR;
		}
	}
	else
	{
		input = 0;
	}

	switch (input)
	{
	case 1:
		if (checkUp(*mapGrid) != 1)
		{
			direction = input;
		}
		break;
	case 2:
		if (checkLeft(*mapGrid) != 1)
		{
			direction = input;
		}
		break;
	case 3:
		if (checkDown(*mapGrid) != 1)
		{
			direction = input;
		}
		break;
	case 4:
		if (checkRight(*mapGrid) != 1)
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
		if (checkUp(*mapGrid) != 1)
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
		if (checkLeft(*mapGrid) != 1)
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
		if (checkDown(*mapGrid) != 1)
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
		if (checkRight(*mapGrid) != 1)
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

	move(dt);
}

ghost::~ghost()
{
}
