#include "Game.h"
#include <iostream>

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
	for (int i = 0; i < 30; ++i)
		for (int j = 0; j < 15; ++j)
			p_Renderer->CreateSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j), glm::vec2(50.0f + i * 30.0f, 50.0f + j * 30.0f), glm::vec2(20.0f, 20.0f), 1);

	p_Renderer->CreateSimpleRenderable("r1", glm::vec2(p_Window->GetWidth()/2, p_Window->GetHeight() / 2), glm::vec2(300.0f, 50.0f), 1);
	p_Renderer->CreateSimpleRenderable("r2", glm::vec2(480.0f, 170.0f), glm::vec2(50.0f, 50.0f), 1);
	p_Renderer->CreateSimpleRenderable("r3", glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f));
}

void Game::Tick(float fDeltaTime)
{ 	
	p_Renderer->GetSimpleRenderable("r1")->SetColor(glm::vec4(col, 1.0f, 0.0f, 1.0f));
	p_Renderer->GetSimpleRenderable("r1")->SetPosition(glm::vec2(p_Window->GetWidth()/2, p_Window->GetHeight()/2));

	p_Renderer->GetSimpleRenderable("r2")->SetColor(glm::vec4(0.0f, 1.0f, col, 1.0f));
	p_Renderer->GetSimpleRenderable("r2")->SetRotation(glm::vec3(0.0f, 0.0f, rot));

	p_Renderer->GetSimpleRenderable("r3")->SetRotation(glm::vec3(0.0f, 0.0f, rot));
	p_Renderer->GetSimpleRenderable("r1")->ModifyBuffer(glm::vec2(50.0f*col, 25.0f*col), glm::vec2(300.0f, 50.0f), 1);

	for (int i = 0; i < 30; ++i)
		for (int j = 0; j < 15; ++j)
			p_Renderer->GetSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j))->SetRotation(glm::vec3(0.0f, 0.0f, rot));
	

	if (col > 1.0f)
		increment = -0.0015f;
	else if (col < 0.0f)
		increment = 0.0015f;

	col += increment * fDeltaTime;
	rot += 0.0015f * fDeltaTime;
}
