/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 2 , 2 }),
	goal(rng, brd, snek, bricks)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameIsOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			if (!(snek.GetDirection() == Snake::Direction::Down) &&
				!(snek.GetDirection() == Snake::Direction::Up))
			{
				delta_loc = { 0 , -1 };
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			if (!(snek.GetDirection() == Snake::Direction::Up) &&
				!(snek.GetDirection() == Snake::Direction::Down))
			{
				delta_loc = { 0 , 1 };
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			if (!(snek.GetDirection() == Snake::Direction::Right)&& 
				!(snek.GetDirection() == Snake::Direction::Left))
			{
				delta_loc = { -1 , 0 };
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			if (!(snek.GetDirection() == Snake::Direction::Left) &&
				!(snek.GetDirection() == Snake::Direction::Right))
			{
				delta_loc = { 1 , 0 };
			}
		}

		++snekMoveCounter;
		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter = 0;
			Location next = snek.GetNextHeadLocation(delta_loc);	
			if (!brd.IsInsideBoard(next)||
				snek.IsInTileExceptEnd(next) ||
				bricks.IsIntile(next))
			{
				gameIsOver = true;
			}
			else
			{
				snek.MoveBy(delta_loc);

				const bool eating = next == goal.GetLocation();
				if (eating)
				{
					snek.Grow(rng);
					goal.Respawn(rng, brd, snek, bricks);
				}



				bricks.AddSegment(rng, brd, snek, goal.GetLocation());
			}
		}
	}
}

void Game::ComposeFrame()
{
	brd.DrawBoard();
	bricks.Draw(brd);
	snek.Draw(brd);
	goal.Draw(brd);
	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver(358, 268, gfx);
	}
}
