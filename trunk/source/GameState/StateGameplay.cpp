#include "stdafx.h"

#include "StateGameplay.h"

bool StateGameplay::Init()
{
	_background = new Image("background.png");
	_background->loadImage();

	return true;
}

void StateGameplay::Update(float dt)
{

}

void StateGameplay::Render(Graphics* g)
{
	g->drawImage(_background, Rect(0, 0, 800, 600));
}