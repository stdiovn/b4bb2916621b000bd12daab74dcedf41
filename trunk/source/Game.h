#pragma once

using namespace stdio_fw;
class Game : public Application
{
public:
	Game();
	virtual ~Game();

	virtual ErrorCode	Init(int screenW, int screenH, const char* title);
	virtual void		Update(float deltaTime);

	virtual void		Render(Graphics* g);
	virtual void		Exit();
};