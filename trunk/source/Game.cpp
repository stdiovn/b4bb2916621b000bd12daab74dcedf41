#include "stdafx.h"

#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

ErrorCode Game::Init(int screenW, int screenH, const char* title)
{
	ErrorCode errCode = Application::Init(screenW, screenH, title);	

	return errCode;
}

void Game::Update(float deltaTime)
{
	
}

void Game::Render(Graphics* g)
{
	g->cleanScreen();	
}

void Game::Exit()
{
	
}