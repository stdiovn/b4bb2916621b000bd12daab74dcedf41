#include "stdafx.h"

#include "StateManager.h"

StateManager* StateManager::s_sharedInstance = NULL;

StateManager* StateManager::GetInstance()
{
	if (s_sharedInstance == NULL)
	{
		s_sharedInstance = new StateManager();
	}

	return s_sharedInstance;
}

StateManager::StateManager()
:_currentState(NULL)
{

}

void StateManager::InitState(GameState* state)
{
	SwitchState(state);
}

void StateManager::Update(float dt)
{
	_currentState->Update(dt);
}

void StateManager::Render(Graphics* g)
{
	_currentState->Render(g);
}

void StateManager::SwitchState(GameState* state)
{
	_currentState = state;
	_currentState->Init();
}
