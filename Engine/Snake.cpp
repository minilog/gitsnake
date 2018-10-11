#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);

	if (delta_loc == Location{ 0, -1 })
	{
		direction = Snake::Direction::Up;
	}
	if (delta_loc == Location{ 0 , 1 })
	{
		direction = Snake::Direction::Down;
	}
	if (delta_loc == Location{ -1, 0 })
	{
		direction = Snake::Direction::Left;
	}
	if (delta_loc == Location{ 1, 0 })
	{
		direction = Snake::Direction::Right;
	}
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{ 
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow(std::mt19937 & rng)
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody(rng);
		++nSegments;
		segments[nSegments - 1].Follow(segments[0]);
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = nSegments - 1; i >= 0; --i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	for (int i = 0; i < nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location & target) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsIntileSnakeAndTwoNextSegments(const Location & target) const
{
	Location nextLoc1 = segments[0].GetLocation(), nextLoc2 = { 0 ,0 };
	if (direction == Snake::Direction::Up)
	{
		nextLoc1.Add(Location{ 0, -1 });
		nextLoc2 = nextLoc1;
		nextLoc2.Add(Location{ 0, -1 });
	}
	else if (direction == Snake::Direction::Down)
	{
		nextLoc1.Add(Location{ 0, 1 });
		nextLoc2 = nextLoc1;
		nextLoc2.Add(Location{ 0, 1 });
	}
	else if (direction == Snake::Direction::Left)
	{
		nextLoc1.Add(Location{ -1, 0 });
		nextLoc2 = nextLoc1;
		nextLoc2.Add(Location{ -1, 0 });
	}
	else if (direction == Snake::Direction::Right)
	{
		nextLoc1.Add(Location{ 1, 0 });
		nextLoc2 = nextLoc1;
		nextLoc2.Add(Location{ 1, 0 });
	}

	if (nextLoc1 == target ||
		nextLoc2 == target)
	{
		return true;
	}


	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

const Snake::Direction& Snake::GetDirection() const
{
	return direction;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(std::mt19937 & rng)
{
	std::uniform_int_distribution<int> cDist( 25, 35);

	c = ( 100, 5 * cDist(rng), 5 * cDist(rng));
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
