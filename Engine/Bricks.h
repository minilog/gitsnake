#pragma once
#include "Snake.h"
#include <random>

class Bricks
{
	class SegmentBrick
	{
	public:
		void Draw(Board& brd);
		void SetLocation(const Location& in_loc);
		const Location& GetLocation() const;
	private:
		Location loc;
		static constexpr Color bodyColor = { 217, 217, 217 };
	};
public:
	void AddSegment(std::mt19937& rng, const Board& brd, const Snake& snake, const Location& goalLoc);
	void Draw(Board& brd);
	bool IsIntile(const Location& nextSnakeLoc) const;
private:
	static constexpr int nSegmentsMax = 100;
	SegmentBrick segments[nSegmentsMax];
	int nSegments = 1;
};

