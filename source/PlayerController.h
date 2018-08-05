#pragma once
#include "Controller.h"
#include "input.h"

class PlayerController :
	public Controller
{
public:
	PlayerController(Input * inputSys);
	~PlayerController();
private:
	void get_input();
	void set_direction();
	void set_velocity();
	void move();

	Input* inputManager;
	int input;
};

