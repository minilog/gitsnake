#pragma once

#include "Snake.h"
#include "Bricks.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake, const Bricks& bricks);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, const Bricks& bricks);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Red;
	Location loc;
};

