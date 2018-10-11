#include "Bricks.h"

void Bricks::AddSegment(std::mt19937 & rng, const Board & brd, const Snake & snake, const Location& goalLoc)
{
	if (nSegments < nSegmentsMax)
	{
		++nSegments;

		std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
		std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

		Location newLoc;

		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (snake.IsIntileSnakeAndTwoNextSegments(newLoc) || newLoc == goalLoc);

		segments[nSegments - 1].SetLocation(newLoc);
	}
}

void Bricks::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Bricks::IsIntile(const Location & nextSnakeLoc) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == nextSnakeLoc)
		{
			return true;
		}
	}

	return false;
}

void Bricks::SegmentBrick::Draw(Board & brd)
{
	brd.DrawCell(loc, bodyColor);
}

void Bricks::SegmentBrick::SetLocation(const Location & in_loc)
{
	loc = in_loc;
}

const Location & Bricks::SegmentBrick::GetLocation() const
{
	return loc;
}
