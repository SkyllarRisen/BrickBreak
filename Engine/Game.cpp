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
	mainBall(gameBoard, 10, Vec2D(200,200), Vec2D(400, 400), Colors::Yellow),
	userPaddle(gameBoard, RectD( Vec2D( gameBoard.PlayZone().GetCenter()[0]-60, gameBoard.PlayZone().Bottom() - 130), Vec2D( gameBoard.PlayZone().GetCenter()[0] + 60, gameBoard.PlayZone().Bottom() - 100) ), 500, Colors::White)
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
	double elapsedTime = ft.Mark();
	while (elapsedTime > 0.0)
	{
		const double dt = std::min(0.001, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	
	ComposeFrame();
	gfx.EndFrame();
}

bool Game::GameOver() const
{
	return abortGame;
}

void Game::UpdateModel(const double dt)
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		abortGame = true;
	int brokenBrickCounter = 0;
	for (Brick& b : brickField)
	{
		if (b.IsBroken())
			++brokenBrickCounter;
	}
	if (brokenBrickCounter == bricksTotal)
	{
		abortGame = true;
	}
	int index = 0;
	double distance = 1000000000;

	userPaddle.Update(wnd.kbd, dt);

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
	mainBall.Collision(userPaddle, dt);
	if (!mainBall.Update(dt))
	{
		abortGame = true;	
	}
}

void Game::ComposeFrame()
{
	gameBoard.Draw();
	userPaddle.Draw();
	mainBall.Draw();
	for (const Brick& b : brickField)
		b.Draw();
	
}
