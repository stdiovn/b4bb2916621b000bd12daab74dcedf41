#include "stdafx.h"

#include "StdioWorld.h"
#include "Constants.h"

void StdioWorld::init()
{
	float screenWidth = 800.0f;
	float screenHeight = 600.0f;
	_mapWidth = _mapHeight = screenHeight*0.8f;
	_mapX = _mapY = screenHeight*0.1f;

	_cellTexture = new Image("block.png");
	_cellTexture->loadImage();
}

void StdioWorld::load(const char* filepath)
{
	FILE* f = fopen(filepath, "r");
	
	if (f == NULL)
	{
		printf("Can't load %s\n", filepath);
		return;
	}

	fscanf(f, "%d", &_numRows);
	fscanf(f, "%d", &_numCols);

	_cellWidth = _mapWidth/(_numCols+2);
	_cellHeight = _mapHeight/(_numRows+2);

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
			int cell = CELL_SPACE;

			fscanf(f, "%d", &cell);

			_worldMatrix[r][c] = cell;
		}
	}

	// add wall
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
				g->drawImage(_cellTexture, Rect(_mapX + c*_cellWidth, _mapY + r*_cellHeight, _cellWidth, _cellHeight));
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