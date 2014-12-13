#pragma once

using namespace stdio_fw;

#define		CELL_SPACE		0
#define		CELL_ROCK		1
#define		CELL_GEM		2
#define		CELL_WALL_NORTH	3
#define		CELL_WALL_EAST	4
#define		CELL_WALL_SOUTH	5
#define		CELL_WALL_WEST	6

class StdioWorld
{
public:
	void					init();
	void					load(const char* filepath);
	void					render(Graphics* g);

	bool					isBlocked(unsigned int row, unsigned int col);
	bool					isBlockedInDirection(unsigned int row, unsigned int col, int direction);

	inline unsigned int		getMapX() { return _mapX; }
	inline unsigned int		getMapY() { return _mapY; }
	inline int				getCell(unsigned int row, unsigned int column) { return _worldMatrix[row][column]; }
	inline unsigned int		getCellWidth() { return _cellWidth; }
private:
	int**			_worldMatrix;
	unsigned int	_numRows;
	unsigned int	_numCols;

	unsigned int	_mapX;
	unsigned int	_mapY;
	unsigned int	_cellWidth;

	Image*			_cellTexture;
};