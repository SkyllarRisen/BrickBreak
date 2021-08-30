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
#include "Colors.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	gameBoard(gfx,RectD(Vec2D(Graphics::ScreenWidth / 2 - (brickWidth*bricksAcross+20) / 2 - 1, 0), brickWidth * bricksAcross + 20, 1079),10),
	mainBall(gameBoard, 10, Vec2D(200,200), Vec2D(400, 400), Colors::Yellow)
{
	for (int i = 0; i < bricksAcross; ++i)
	{
		for (int j = 0; j < bricksLayers; ++j)
		{
			Color tmpColor;
			switch (i%6)
			{
			case 0:
				tmpColor = Colors::Blue;
				break;
			case 1:
				tmpColor = Colors::Green;
				break;
			case 2:
				tmpColor = Colors::Red;
				break;
			case 3:
				tmpColor = Colors::Yellow;
				break;
			case 4:
				tmpColor = Colors::Cyan;
				break;
			case 5:
				tmpColor = Colors::Magenta; 
				break;
			default:
				tmpColor = Colors::White;
			}
			brickField.push_back(Brick(gameBoard, RectD(Vec2D(0,30) + Vec2D(i* brickWidth,j*brickHeight), brickWidth, brickHeight), tmpColor));
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

bool Game::GameOver() const
{
	return abortGame;
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		abortGame = true;
	const double dt = ft.Mark();
	int index = 0;
	double distance = 1000000000;

	for (int i = 0; i < brickField.size();++i)
	{
		if (mainBall.IsColliding(brickField.at(i), dt))
		{
			double newDist = (brickField.at(i).GetRect().GetCenter()-(mainBall.Pos()+mainBall.Vel()*dt).Get2D()).NormSq();
			if (newDist < distance)
			{
				distance = newDist;
				index = i+1;
			}
		}
	}
	if(index)
		mainBall.Collision(brickField.at(index-1), dt);
	mainBall.Update(dt);
}

void Game::ComposeFrame()
{
	gameBoard.Draw();
	mainBall.Draw();
	for (const Brick& b : brickField)
		b.Draw();
	
}
