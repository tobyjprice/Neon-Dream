#pragma once
#include "sprite.h"

class Controller
{
public:
	Controller();
	~Controller();

	void update();

private:
	virtual void processInput();
	sprite* sprite;
};

