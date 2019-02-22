#include "Game.h"

Game::Game()
{
	Init();
	Loop();
}

Game::~Game()
{
}

void Game::Init()
{
}

void Game::Loop()
{
	while (window.ShouldNotClose()) 
	{
		window.Clear();
		window.Draw();
		window.SwapBuffers();
		window.PollEvents();
	}
}
