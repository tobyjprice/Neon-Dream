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
	sprite* tempSprite = new sprite(16, 16, 80, 80, "resources//test.bmp", gameRenderer);
	spriteList.push_back(tempSprite);

	tempSprite = new sprite(16, 16, 0, 0, "resources//test2.bmp", gameRenderer);
	spriteList.push_back(tempSprite);
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
			int pointType = mapGrid[getArrPos(y, x, mapWidth)];

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
				tempSprite = new sprite(8, 8, x * 8, y * 8, "resources//pathTest.bmp", gameRenderer);
				spriteList.push_back(tempSprite);
				break;
			case 3:
				tempSprite = new sprite(8, 8, x * 8, y * 8, "resources//pathTest.bmp", gameRenderer);
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

int game_state::getArrPos(int i, int j, int width)
{
	int k = (i * width) + j;

	return k;
}

sprite* game_state::getSprite(int spriteId)
{
	return spriteList[spriteId];
}

