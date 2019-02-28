#include "Game.h"

Game::Game()
{
	Begin();
	Loop();
}

Game::~Game()
{	
}

void Game::Begin()
{	
	p_Renderer->CreateSimpleRenderable("r1", glm::vec2(0.0f, 0.0f), glm::vec2(300.0f, 50.0f), 1);
	p_Renderer->CreateSimpleRenderable("r2", glm::vec2(480.0f, 170.0f), glm::vec2(50.0f, 50.0f), 1);
	p_Renderer->CreateSimpleRenderable("r3", glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f));

	for (int i = 0; i < 8; ++i)	
		p_Renderer->CreateSimpleRenderable("rend" + std::to_string(i), glm::vec2(100.0f + i * 100.0f, 400.0f), glm::vec2(20.0f, 20.0f), 1);	
}

void Game::Tick()
{ 	
	p_Renderer->GetSimpleRenderable("r1")->SetColor(glm::vec4(col, 1.0f, 0.0f, 1.0f));
	p_Renderer->GetSimpleRenderable("r1")->SetPosition(glm::vec2(col*200+380, 270.0f));

	p_Renderer->GetSimpleRenderable("r2")->SetColor(glm::vec4(0.0f, 1.0f, col, 1.0f));
	p_Renderer->GetSimpleRenderable("r2")->SetRotation(glm::vec3(0.0f, 0.0f, rot));

	p_Renderer->GetSimpleRenderable("r3")->SetRotation(glm::vec3(0.0f, 0.0f, rot));

	for (int i = 0; i < 8; ++i)
		p_Renderer->GetSimpleRenderable("rend" + std::to_string(i))->SetRotation(glm::vec3(0.0f, 0.0f, rot));
	
	if (col > 1.0f)
		increment *= -1.0f;
	else if (col < 0.0f)
		increment *= -1.0f;

	col += increment;
	rot += 0.02f;
}
