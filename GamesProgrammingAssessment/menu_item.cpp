#include "menu_item.h"

menu_item::menu_item(char* inText, int x, int y, int w, int h, SDL_Renderer* inRenderer)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	text = inText;
	renderer = inRenderer;
	defColor = { 255, 255, 255 };
	value = 0;

	if (TTF_Init() == -1)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init Error: %s\n", SDL_GetError());
	}

	font = TTF_OpenFont("C://Users//Toby//Documents//University//Games-Programming-Assessment//GamesProgrammingAssessment//resources//true-crimes.ttf", 28);

	update_texture();
}

void menu_item::set_highlight()
{
	texture = highTexture;
}

void menu_item::set_default()
{
	texture = defTexture;
}

void menu_item::update_texture()
{
	surface = TTF_RenderText_Solid(font, text, defColor);
	defTexture = SDL_CreateTextureFromSurface(renderer, surface);

	surface = TTF_RenderText_Solid(font, text, { 100,0,100 });
	highTexture = SDL_CreateTextureFromSurface(renderer, surface);

	texture = defTexture;
}

void menu_item::set_text(char* inText)
{
	text = inText;
	update_texture();
}

menu_item::~menu_item()
{
}
