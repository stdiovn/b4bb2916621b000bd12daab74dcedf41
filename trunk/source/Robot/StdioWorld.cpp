#include "stdafx.h"

#include "StdioWorld.h"
#include "Constants.h"

void StdioWorld::init()
{
	_mapX = 10;
	_mapY = 10;
	_cellWidth = 50;

	_cellTexture = new Image("block.png");
	_cellTexture->loadImage();
}

void StdioWorld::load(const char* filepath)
{
	_numRows = 10;
	_numCols = 10;

	_worldMatrix = new int*[_numRows+2];

	for (unsigned int r = 0; r < _numRows+2; r++)
	{
		_worldMatrix[r] = new int[_numCols+2];
	}

	// init default world
	for (unsigned int r = 1; r < _numRows+1; r++)
	{
		for (unsigned int c = 1; c < _numCols+1; c++)
		{
			_worldMatrix[r][c] = CELL_SPACE;
		}
	}

	for (unsigned int r = 1; r < _numRows + 1; r++)
	{
		_worldMatrix[r][0] = CELL_WALL_WEST;
		_worldMatrix[r][_numCols + 1] = CELL_WALL_EAST;
	}

	for (unsigned int c = 1; c < _numCols + 1; c++)
	{
		_worldMatrix[0][c] = CELL_WALL_NORTH;
		_worldMatrix[_numRows+1][c] = CELL_WALL_SOUTH;
	}
}

void StdioWorld::render(Graphics* g)
{
	for (unsigned int r = 0; r < _numRows+2; r++)
	{
		for (unsigned int c = 0; c < _numCols+2; c++)
		{
			if (_worldMatrix[r][c] != CELL_SPACE)
			{
				g->drawImage(_cellTexture, Rect(_mapX + c*_cellWidth, _mapY + r*_cellWidth, _cellWidth, _cellWidth));
			}
		}
	}
}

bool StdioWorld::isBlocked(unsigned int row, unsigned int col)
{
	return (_worldMatrix[row][col] != CELL_SPACE);
}

bool StdioWorld::isBlockedInDirection(unsigned int row, unsigned int col, int direction)
{
	switch (direction)
	{
	case FACING_NORTH:
		return isBlocked(row - 1, col);
		break;
	case FACING_EAST:
		return isBlocked(row, col + 1);
		break;
	case FACING_SOUTH:
		return isBlocked(row + 1, col);
		break;
	case FACING_WEST:
		return isBlocked(row, col - 1);
		break;
	default:
		return true;
	}
}