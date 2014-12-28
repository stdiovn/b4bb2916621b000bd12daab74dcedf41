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

	_gemTexture = new Image("gem.png");
	_gemTexture->loadImage();
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

			if (cell == CELL_GEM)
			{
				setNumGemsAt(r, c, 1);
			}
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
			if (_worldMatrix[r][c] == CELL_ROCK || isWall(r, c))
			{
				g->drawImage(_cellTexture, Rect(_mapX + c*_cellWidth, _mapY + r*_cellHeight, _cellWidth, _cellHeight));
			}
			
			int numGems = getNumGemsAt(r, c);
			if (numGems > 0)
			{
				g->drawImage(_gemTexture, Rect(_mapX + c*_cellWidth, _mapY + r*_cellHeight, _cellWidth, _cellHeight));
				char buf[4] = { 0 };
				sprintf(buf, "%d", numGems);
				g->setColor(0xffffffff);
				g->drawText(buf, _mapX + c*_cellWidth, _mapY + r*_cellHeight);
			}
		}
	}
}

bool StdioWorld::isBlocked(unsigned int row, unsigned int col)
{
	int cell = _worldMatrix[row][col];
	return (cell == CELL_ROCK || isWall(row, col));
}

bool StdioWorld::isWall(unsigned int row, unsigned int col)
{
	int cell = _worldMatrix[row][col];

	return (cell == CELL_WALL_EAST || cell == CELL_WALL_NORTH || cell == CELL_WALL_SOUTH || cell == CELL_WALL_WEST);
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

int StdioWorld::getNumGemsAt(unsigned int row, unsigned int col)
{
	if (row == 0 || row == _numRows + 1 || col == 0 || col == _numCols + 1)
	{
		return 0;
	}

	return (_worldMatrix[row][col] & 0xffff0000) >> 16;
}

void StdioWorld::setNumGemsAt(unsigned int row, unsigned int col, int numGems)
{
	_worldMatrix[row][col] &= 0xffff;
	_worldMatrix[row][col] |= (numGems << 16);
}