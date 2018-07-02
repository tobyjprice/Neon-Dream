#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class log_item
{
public:
	log_item();
	log_item(log_item* copy);
	log_item(int x, int y, int w, int h, char* inText, SDL_Renderer* inRenderer, int priority, TTF_Font* inFont);
	~log_item();
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
	TTF_Font* font;
	char* text;
	SDL_Color color;
};

