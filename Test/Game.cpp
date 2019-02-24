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
	SimpleRenderable r1(  0.0f,  0.0f, 1.0f, 0.2f, 1);
	SimpleRenderable r2( 0.0f, -0.3f, 0.2f, 0.2f, 1);
	SimpleRenderable r3(-1.0f, -1.0f, 0.2f, 0.2f);
	
	float col = 0.0f;
	float increment = 0.01f;
	while (p_Window->ShouldNotClose()) 
	{
		p_Renderer->Clear();

		r1.SetColor(col, 0.0f, 1.0f, 1.0f);
		r2.SetColor(0.0f, col, 1.0f, 1.0f);

		r1.Draw();
		r2.Draw();
		r3.Draw();

		if (col > 1.0f)
			increment = -0.05f;
		else if (col < 0.0f)
			increment = 0.05f;

		col += increment;

		p_Window->SwapBuffers();
		p_Window->PollEvents();
	}
}
