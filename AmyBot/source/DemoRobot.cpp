#include "stdafx.h"

#include "DemoRobot.h"

void DemoRobot::run()
{
	turnLeft();
	turnLeft();

	while (true)
	{
		while (!frontIsBlocked())
		{
			move();
		}
		turnLeft();
	}
}