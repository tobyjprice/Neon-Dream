#pragma once
#include <list>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "log_item.h"
#include <chrono>
#include <ctime>

class log_system
{
public:
	log_system(SDL_Renderer* inRenderer);
	~log_system();
	struct logText
	{
		std::string str;
		int priority;
	};
	std::list<logText> logList;
	std::vector<log_item> logOutput;
	log_item frameRateItem;
	log_item scoreItem;
	TTF_Font* font;
	SDL_Renderer* renderer;
	void addLog(std::string inStr, int priority);
	void frameRate(double frameTimeSec);
	void showScore(int score);
	void update();
};

