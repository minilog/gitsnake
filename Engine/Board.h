#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& in_gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBoard();
private:
	static constexpr int dimension = 20;
	static constexpr int width = 36;
	static constexpr int height = 26;
	static constexpr int x = 2;
	static constexpr int y = 2;
	Graphics& gfx;
};