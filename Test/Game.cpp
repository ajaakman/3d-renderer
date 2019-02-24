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
	SimpleRenderable renderable(0.2);
	SimpleRenderable renderable2(-0.2);
	
	float r = 0.0f;
	float increment = 0.05f;
	while (window->ShouldNotClose()) 
	{
		window->Clear();

		renderable.UpdateUniforms(r);
		renderable2.UpdateUniforms(r);

		renderable.Draw();
		renderable2.Draw();

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;

		window->SwapBuffers();
		window->PollEvents();
	}
}
