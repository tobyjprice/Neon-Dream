#pragma once
#include "SDL.h"
#include <vector>
#include "SDL_ttf.h"

class menu_item
{
public:
	menu_item(char* text, int x, int y, int w, int h, SDL_Renderer* renderer);
	~menu_item();
	void set_highlight();
	void set_default();
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Texture* defTexture;
	SDL_Texture* highTexture;
	SDL_Rect rect;
	TTF_Font* font;
	SDL_Color defColor;
	char* text;
};

