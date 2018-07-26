#pragma once
#include "Controller.h"

class PlayerController :
	public Controller
{
public:
	PlayerController();
	~PlayerController();
private:
	void processInput();
};

