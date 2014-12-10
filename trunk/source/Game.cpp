#include "stdafx.h"

#include "Game.h"
#include "Manager/StateManager.h"
#include "GameState/StateGameplay.h"

Game::Game()
{

}

Game::~Game()
{

}

ErrorCode Game::Init(int screenW, int screenH, const char* title)
{
	ErrorCode errCode = Application::Init(screenW, screenH, title);	

	StateManager::GetInstance()->InitState(new StateGameplay());

	return errCode;
}

void Game::Update(float deltaTime)
{
	StateManager::GetInstance()->Update(deltaTime);
}

void Game::Render(Graphics* g)
{
	g->cleanScreen();	

	StateManager::GetInstance()->Render(g);
}

void Game::Exit()
{
	
}