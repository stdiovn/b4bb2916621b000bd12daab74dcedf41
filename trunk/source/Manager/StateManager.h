#pragma once

#include "GameState/GameState.h"

class StateManager
{
public:
	static StateManager*		GetInstance();

	void						InitState(GameState* state);
	void						Update(float dt);
	void						Render(Graphics* g);

	void						SwitchState(GameState* state);
protected:
	StateManager();
private:
	GameState*					_currentState;

	static StateManager*		s_sharedInstance;
};