#pragma once

using namespace stdio_fw;

class GameState
{
public:
	virtual bool		Init() { return true; };
	virtual void		Render(Graphics* g) {};
	virtual void		Update(float dt) {};
	virtual void		Release() {};
};