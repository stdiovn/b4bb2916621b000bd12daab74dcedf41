#pragma once

#include "GameState.h"

using namespace stdio_fw;

class StateGameplay : public GameState
{
public:
	bool			Init();
	void			Update(float dt);
	void			Render(Graphics* g);
private:
	Image*			_background;
};