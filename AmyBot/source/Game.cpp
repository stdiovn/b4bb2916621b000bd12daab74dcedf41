#include "stdafx.h"

#include "Game.h"
#include "Robot\StdioWorld.h"
#include "DemoRobot.h"

Game::Game()
{

}

Game::~Game()
{

}

ErrorCode Game::Init(int screenW, int screenH, const char* title)
{
	ErrorCode errCode = Application::Init(screenW, screenH, title);

	_world = new StdioWorld();
	_world->init();
	_world->load("sample.map");

	_robot = new DemoRobot();
	_robot->setWorld(_world);
	_robot->init();

	Font::initFontLib();
	_font = new Font("arial.ttf");
	_font->loadFont();

	return errCode;
}

void Game::Update(float deltaTime)
{
	_robot->update(deltaTime);
}

void Game::Render(Graphics* g)
{
	g->setFont(_font);

	g->cleanScreen();	

	_world->render(g);
	_robot->render(g);
}

void Game::Exit()
{
	
}