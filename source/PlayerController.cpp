#include "PlayerController.h"



PlayerController::PlayerController(Input* inputSys)
{
	inputManager = inputSys;
}


PlayerController::~PlayerController()
{
}

void PlayerController::get_input()
{
	input = inputManager->get_current_input();

}

void PlayerController::set_direction()
{
	/*switch (input)
	{
	case 1:
		if (checkUp(*mapGrid) != 1 && checkUp(*mapGrid) != 4)
		{
			if (xPosInt >= xGridPos * 8 && xPosInt + 8 <= (xGridPos * 8) + 8)
			{
				direction = input;
			}
		}
		break;
	case 2:
		if (checkDown(*mapGrid) != 1 && checkDown(*mapGrid) != 4)
		{
			if (xPosInt >= xGridPos * 8 && xPosInt + 8 <= (xGridPos * 8) + 8)
			{
				direction = input;
			}
		}
		break;
	case 3:
		if (checkLeft(*mapGrid) != 1 && checkLeft(*mapGrid) != 4)
		{
			if (yPosInt >= yGridPos * 8 && yPosInt + 8 <= (yGridPos * 8) + 8)
			{
				direction = input;
			}
		}
		break;
	case 4:
		if (checkRight(*mapGrid) != 1 && checkRight(*mapGrid) != 4)
		{
			if (yPosInt >= yGridPos * 8 && yPosInt + 8 <= (yGridPos * 8) + 8)
			{
				direction = input;
			}

		}
		break;
	case 5:
		if (speed == 80)
		{
			speed = 160;
		}
		break;
	default:
		break;
	}*/
}

void PlayerController::set_velocity()
{
}

void PlayerController::move()
{
}
