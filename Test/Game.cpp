#include "Game.h"

Game::Game()
{
	window = new Window();
	Init();
	Loop();
}

Game::~Game()
{
	delete window;
}

void Game::Init()
{	
}

void Game::Loop()
{
	SimpleRenderable renderable(0.2f, 0.2f);
	SimpleRenderable renderable2(-0.2f, 0.3f);
	
	float col = 0.0f;
	float increment = 0.01f;
	while (window->ShouldNotClose()) 
	{
		window->Clear();

		renderable.SetColor(col, 0.0f, 1.0f, 1.0f);
		renderable2.SetColor(0.0f, col, 1.0f, 1.0f);

		renderable.Draw();
		renderable2.Draw();

		if (col > 1.0f)
			increment = -0.05f;
		else if (col < 0.0f)
			increment = 0.05f;

		col += increment;

		window->SwapBuffers();
		window->PollEvents();
	}
}
