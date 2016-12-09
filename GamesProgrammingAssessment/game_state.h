#pragma once
#include <vector>
#include "sprite.h"

class game_state
{
public:
	game_state();
	~game_state();
	void load_resources();
private:
	std::vector<sprite*> spriteList;
};

