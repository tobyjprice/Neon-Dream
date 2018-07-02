#include "log_item.h"

log_item::log_item()
{
	texture = NULL;
}

log_item::log_item(log_item* copy)
{
	rect.x = copy->rect.x;
	rect.y = copy->rect.y;
	rect.w = copy->rect.w;
	rect.h = copy->rect.h;
	text = copy->text;
	renderer = copy->renderer;

	font = copy->font;

	color = copy->color;

	surface = copy->surface;
	texture = copy->texture;
}

log_item::log_item(int x, int y, int w, int h, char* inText, SDL_Renderer* inRenderer, int priority, TTF_Font* inFont)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	text = inText;
	renderer = inRenderer;

	font = inFont;

	switch (priority)
	{
	case 0:
		// Error
		color = { 255,0,0 };
		break;
	case 1:
		// Warning
		color = { 255,191,0 };
		break;
	case 2:
		// Okay
		color = { 0,255,0 };
		break;
	default:
		// Other
		color = { 255, 255, 255 };
		break;
	}

	surface = TTF_RenderText_Solid(font, text, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}


log_item::~log_item()
{
	
}
