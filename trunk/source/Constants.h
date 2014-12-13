#pragma once

// facing direction
#define FACING_NORTH		0
#define FACING_WEST			1
#define FACING_SOUTH		2
#define FACING_EAST			3

#define RIGHT_OF(direction)	((direction+3)%4)
#define LEFT_OF(direction)	((direction+1)%4)