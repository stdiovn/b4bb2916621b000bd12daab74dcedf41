#include "stdafx.h"
#include "Game.h"

/////////////////////////////////////
// Entry Point
/////////////////////////////////////
void main()
{
	Game g;
	g.Init(800, 600, "Game");

	g.Run();
}