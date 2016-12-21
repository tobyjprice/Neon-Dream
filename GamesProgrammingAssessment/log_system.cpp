#include "log_system.h"

log_system::log_system(SDL_Renderer* inRenderer)
{
	renderer = inRenderer;

	font = TTF_OpenFont("resources//8bitOperatorPlus8-Regular.ttf", 12);
}


log_system::~log_system()
{
}

void log_system::addLog(std::string inStr, int priority)
{
	
	if (logOutput.size() == 10)
	{
		
		SDL_FreeSurface(logOutput.back().surface);
		SDL_DestroyTexture(logOutput.back().texture);
		logOutput.pop_back();
	}
	
	std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();
	time_t time;
	time = std::chrono::system_clock::to_time_t(currTime);
	std::string timeStr = ctime(&time);
	
	timeStr = timeStr.substr(10, 9);
	inStr.insert(0, timeStr + ": ");
	char* str = new char[inStr.length() + 1];
	std::strcpy(str, inStr.c_str());

	log_item* tempItem = new log_item(0, 100, (4*inStr.length()), 7, str, renderer, priority, font);
	log_item deepItem(tempItem);

	logOutput.insert(logOutput.begin(), deepItem);

	
	delete tempItem;
	delete str;

	update();
}

void log_system::update()
{
	for (auto& elem : logOutput) 
	{
		elem.rect.y -= 10;
	}
}

void log_system::frameRate(double frameTimeSec)
{
	int* renW = new int;
	int* renH = new int;
	SDL_RenderGetLogicalSize(renderer, renW, renH);
	std::string inStr = std::to_string(1 / frameTimeSec);
	inStr = inStr.substr(0,inStr.length() - 7);
	char* str = new char[inStr.length() + 1];
	std::strcpy(str, inStr.c_str());
	log_item tempItem(*renW - (4 * inStr.length()) -1, 0, (4 * inStr.length()), 7, str, renderer, 4, font);
	frameRateItem = tempItem;
	delete renW;
	delete renH;
}

void log_system::showScore(int score)
{
	int* renW = new int;
	int* renH = new int;
	SDL_RenderGetLogicalSize(renderer, renW, renH);
	std::string inStr = std::to_string(score);
	inStr.insert(0, "Score - ");
	char* str = new char[inStr.length() + 1];
	std::strcpy(str, inStr.c_str());
	log_item tempItem(*renW - (4 * inStr.length()) - 1, *renH - 10, (4 * inStr.length()), 7, str, renderer, 4, font);
	scoreItem = tempItem;
	delete renW;
	delete renH;
}