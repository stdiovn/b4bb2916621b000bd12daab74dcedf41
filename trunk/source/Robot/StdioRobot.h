#pragma once

#include <queue>

#define ACTION_MOVE			0
#define ACTION_TURNLEFT		1
#define ACTION_PICKGEM		2
#define ACTION_PUTGEM		3

#include "Constants.h"
#include "tinythread\tinythread.h"

using namespace tthread;
using namespace stdio_fw;

class StdioWorld;

class StdioRobot
{
public:
	virtual void			init();
	virtual void			render(Graphics* g);
	virtual void			update(float dt);

	void					reset();

	void					move();
	void					turnLeft();
	void					pickGem();
	void					putGem();
	bool					frontIsBlocked();
	bool					leftIsBlocked();
	bool					rightIsBlocked();
	bool					gemPresent();
	bool					hasGemInBag();
	bool					facingNorth();
	bool					facingEast();
	bool					facingSouth();
	bool					facingWest();

	// simulate actions
	virtual void			run() {};

	inline void				setWorld(StdioWorld* world) { _world = world; }
	inline StdioWorld*		getWorld() { return _world; }
private:
	void					runAction(int action);

	unsigned int			_currentRow;
	unsigned int			_currentColumn;
	unsigned int			_facingDirection;
	unsigned int			_numGemsInBag;

	StdioWorld*				_world;
	Image*					_bodyTexture;
	std::queue<int>			_actions;

	float					_timer;

	thread*					_updateThread;
	thread*					_runThread;
};