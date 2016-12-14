#include "game_state.h"
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

void game_state::load_resources()
{
	sprite* tempSprite = new sprite(12, 12, 108, 184, "resources//test.bmp", gameRenderer);

	tempSprite->xGridPos = 5;
	tempSprite->yGridPos = 5;

	spriteList.push_back(tempSprite);

	load_map();

	/*for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			std::cout << mapGrid[getArrPos(x, y, 28)];
		}
	} */
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

	populate_map();
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
			case 0:
				break;
			case 1:
				tempSprite = new sprite(8, 8, x * 8, y * 8, "resources//Wall-1.bmp", gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 2:
				tempSprite = new sprite(2, 2, (x * 8) + 3, (y * 8) + 3, "resources//pathTest.bmp", gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 3:
				tempSprite = new sprite(4, 4, (x * 8) + 2, (y * 8) + 2, "resources//pathTest.bmp", gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 4:
				tempSprite = new sprite(8, 8, x * 8, y * 8, "resources//test2.bmp", gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			default:
				break;
			}
		}
	}
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

