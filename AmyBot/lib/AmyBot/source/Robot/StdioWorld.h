#pragma once

using namespace stdio_fw;

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
	inline unsigned int		getCellHeight() { return _cellHeight; }
private:
	unsigned int	_mapX;
	unsigned int	_mapY;
	float			_mapWidth;
	float			_mapHeight;

	unsigned int	_cellWidth;
	unsigned int	_cellHeight;

	int**			_worldMatrix;
	unsigned int	_numRows;
	unsigned int	_numCols;

	Image*			_cellTexture;
};