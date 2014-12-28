#include "stdafx.h"

#include "DemoRobot.h"

void DemoRobot::run()
{
	turnLeft();
	turnLeft();

	move();

	turnLeft();
	for (int i = 0; i < 4; i++)
	{
		move();
	}

	pickGem();
	pickGem();
	move();
	move();
	putGem();
	putGem();

	while (true)
	{
		move();
		move();
		move();
		turnLeft();
		move();
		move();
		turnLeft();
	}
}