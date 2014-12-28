#include "stdafx.h"

#include "StdioRobot.h"
#include "StdioWorld.h"

void RunRobotThread(void* arg)
{
	StdioRobot* robot = (StdioRobot*)arg;
	robot->run();
}

void StdioRobot::init()
{
	_timer = 0.0f;

	_currentRow = 1;
	_currentColumn = 1;
	_numGemsInBag = 0;

	_facingDirection = FACING_NORTH;

	_bodyTexture = new Image("robot.png");
	_bodyTexture->loadImage();

	// start update thread
	//_updateThread = new thread(UpdateRobotThread, this);
	_runThread = new thread(RunRobotThread, this);
}

void StdioRobot::render(Graphics* g)
{
	float rotationAngle = 180.0f;

	switch (_facingDirection)
	{
	case FACING_NORTH:
		rotationAngle = 0.0f;
		break;
	case FACING_EAST:
		rotationAngle = 90.0f;
		break;
	case FACING_SOUTH:
		rotationAngle = 180.0f;
		break;
	case FACING_WEST:
		rotationAngle = -90.0f;
		break;
	}

	// convert to radian
	rotationAngle *= 0.0174532925f;

	Mat3 rotationMatrix;
	rotationMatrix.SetRotation(rotationAngle);

	unsigned int mapX = _world->getMapX();
	unsigned int mapY = _world->getMapY();
	unsigned int cellWidth = _world->getCellWidth();
	unsigned int cellHeight = _world->getCellHeight();

	Mat3 translationMatrix;
	translationMatrix.SetTranslation(mapX + (_currentColumn + 0.5f)*cellWidth, mapY + (_currentRow + 0.5f)*cellHeight);

	g->pushMatrix(rotationMatrix);
	g->pushMatrix(translationMatrix);
	g->drawImage(_bodyTexture, Rect(-(cellWidth / 2.0f), -(cellHeight / 2.0f), cellWidth, cellHeight));
	g->popMatrix();
}

void StdioRobot::update(float dt)
{
	_timer += dt;

	return;

	if (_actions.empty()) return;

	if (_timer >= 0.3f)
	{
		_timer = 0.0f;

		int action = _actions.front();

		switch (action)
		{
		case ACTION_MOVE:
			switch (_facingDirection)
			{
			case FACING_NORTH:
				_currentRow--;
				break;
			case FACING_EAST:
				_currentColumn++;
				break;
			case FACING_SOUTH:
				_currentRow++;
				break;
			case FACING_WEST:
				_currentColumn--;
				break;
			}
			break;
		case ACTION_TURNLEFT:
			_facingDirection = (_facingDirection + 1) % 4;
			break;
		case ACTION_PICKGEM:
			break;
		case ACTION_PUTGEM:
			break;
		default:
			;
		}

		_actions.pop();
	}
}

void StdioRobot::reset()
{
	_currentRow = 1;
	_currentColumn = 1;
	_facingDirection = FACING_NORTH;

	_numGemsInBag = 0;
}

void StdioRobot::move()
{
	runAction(ACTION_MOVE);
}

void StdioRobot::turnLeft()
{
	runAction(ACTION_TURNLEFT);
}

void StdioRobot::pickGem()
{
	runAction(ACTION_PICKGEM);
}

void StdioRobot::putGem()
{
	runAction(ACTION_PUTGEM);
}

bool StdioRobot::frontIsBlocked()
{
	return _world->isBlockedInDirection(_currentRow, _currentColumn, _facingDirection);
}

bool StdioRobot::leftIsBlocked()
{
	return _world->isBlockedInDirection(_currentRow, _currentColumn, LEFT_OF(_facingDirection));
}

bool StdioRobot::rightIsBlocked()
{
	return _world->isBlockedInDirection(_currentRow, _currentColumn, RIGHT_OF(_facingDirection));
}

bool StdioRobot::gemPresent()
{
	return (_world->getCell(_currentRow, _currentColumn) == CELL_GEM);
}

bool StdioRobot::hasGemInBag()
{
	return (_numGemsInBag > 0);
}

bool StdioRobot::facingNorth()
{
	return (_facingDirection == FACING_NORTH);
}

bool StdioRobot::facingEast()
{
	return (_facingDirection == FACING_EAST);
}

bool StdioRobot::facingSouth()
{
	return (_facingDirection == FACING_SOUTH);
}

bool StdioRobot::facingWest()
{
	return (_facingDirection == FACING_WEST);
}

void StdioRobot::runAction(int action)
{
	if (_timer <= 300.0f)
	{
		Sleep(300.0f - _timer);
	}

	_timer = 0.0f;

	unsigned int numGems = _world->getNumGemsAt(_currentRow, _currentColumn);

	switch (action)
	{
	case ACTION_MOVE:
		switch (_facingDirection)
		{
		case FACING_NORTH:
			_currentRow--;
			break;
		case FACING_EAST:
			_currentColumn++;
			break;
		case FACING_SOUTH:
			_currentRow++;
			break;
		case FACING_WEST:
			_currentColumn--;
			break;
		}
		break;
	case ACTION_TURNLEFT:
		_facingDirection = (_facingDirection + 1) % 4;
		break;
	case ACTION_PICKGEM:
		if (numGems > 0)
		{
			_world->setNumGemsAt(_currentRow, _currentColumn, numGems - 1);
		}
		else
		{
			//TODO: throw exception
		}
		break;
	case ACTION_PUTGEM:
		_world->setNumGemsAt(_currentRow, _currentColumn, numGems + 1);
		break;
	default:
		;
	}
}