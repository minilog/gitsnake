#include "Board.h"
#include <assert.h>

Board::Board(Graphics & in_gfx)
	:
	gfx(in_gfx)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(x * dimension + loc.x * dimension + 1, y * dimension + loc.y * dimension + 1, dimension - 2, dimension - 2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

void Board::DrawBoard()
{
	//Draw top board
	for (int y0 = y * dimension; y0 < y * dimension + 2; ++y0)
	{
		for (int x0 = x * dimension; x0 < (x + width) * dimension; ++x0)
		{
			gfx.PutPixel(x0, y0, { 102, 140, 255 });
		}
	}

	//Draw bottom board
	for (int y0 = (y + height) * dimension - 2; y0 < (y + height) * dimension; ++y0)
	{
		for (int x0 = x * dimension; x0 < (x + width) * dimension; ++x0)
		{
			gfx.PutPixel(x0, y0, { 102, 140, 255 });
		}
	}

	//Draw left board
	for (int x0 = x * dimension; x0 < x * dimension + 2; ++x0)
	{
		for (int y0 = y * dimension; y0 < (y + height) * dimension; ++y0)
		{
			gfx.PutPixel(x0, y0, { 102, 140, 255 });
		}
	}

	//Draw right board
	for (int x0 = (x + width) * dimension - 2; x0 < (x + width) * dimension; ++x0)
	{
		for (int y0 = y * dimension; y0 < (y + height) * dimension; ++y0)
		{
			gfx.PutPixel(x0, y0, { 102, 140, 255 });
		}
	}
}
