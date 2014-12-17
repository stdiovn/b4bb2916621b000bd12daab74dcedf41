#pragma once

// facing direction
#define FACING_NORTH		0
#define FACING_WEST			1
#define FACING_SOUTH		2
#define FACING_EAST			3

#define RIGHT_OF(direction)	((direction+3)%4)
#define LEFT_OF(direction)	((direction+1)%4)

#define		CELL_BOT		9
#define		CELL_SPACE		0
#define		CELL_ROCK		1
#define		CELL_GEM		2
#define		CELL_WALL_NORTH	3
#define		CELL_WALL_EAST	4
#define		CELL_WALL_SOUTH	5
#define		CELL_WALL_WEST	6

#define ACTION_MOVE			0
#define ACTION_TURNLEFT		1
#define ACTION_PICKGEM		2
#define ACTION_PUTGEM		3
