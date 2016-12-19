#include "game_state.h"
#include "SDL_image.h"
#include <iostream>
#include <sstream>
#include <fstream>

game_state::game_state(SDL_Renderer *renderer)
{
	gameRenderer = renderer;
	mapGrid.reserve(28 * 31);
	mapWidth = 28;
	mapHeight = 31;
}


game_state::~game_state()
{
}

void game_state::load_new_game()
{
	paused = false;
	load_resources();
	load_map();
	populate_map();
	load_sprites();
}

void game_state::load_resources()
{
	playerSurface = IMG_Load("resources//test.bmp");
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
				tempSprite = new sprite(8, 8, x * 8, y * 8, getWallSurface(x, y, mapWidth), gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 2: // Pellet
				tempSprite = new sprite(2, 2, (x * 8) + 3, (y * 8) + 3, pellet, gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 3: // Power up
				tempSprite = new sprite(4, 4, (x * 8) + 2, (y * 8) + 2, powerup, gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 4: // Ghost Gate
				tempSprite = new sprite(8, 8, x * 8, y * 8, ghostWall, gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			default:
				break;
			}
		}
	}
}

void game_state::load_sprites()
{
	sprite* tempSprite = new sprite(12, 12, 108, 184, playerSurface, gameRenderer);

	tempSprite->xGridPos = 5;
	tempSprite->yGridPos = 5;

	spriteList.push_back(tempSprite);
	player = tempSprite;

	ghost* tempGhost = new ghost(12, 12, 108, 88, powerup, gameRenderer);
	spriteList.push_back(tempGhost);
	ghostList.push_back(tempGhost);

	for (int x = 0; x < 3; x++)
	{
		ghost* tempGhost = new ghost(12, 12, 108/*94 + (x * 14)*/, 88/*118*/, powerup, gameRenderer);
		spriteList.push_back(tempGhost);
		ghostList.push_back(tempGhost);
	}
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

	if (y == 30 && x == 0)
	{
		std::cout << "found" << std::endl;
	}

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
	player->update(dt, spriteList[0], &mapGrid);

	for (auto& elem : ghostList)
	{
		elem->update(dt, spriteList[0], &mapGrid);

		if (checkCollision(player, elem))
		{
			SDL_Log("COLLISION");
		}
		else
		{
			//SDL_Log("NOTHING");
		}
	}
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

