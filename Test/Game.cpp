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
	//for (int i = 0; i < 30; ++i)
	//	for (int j = 0; j < 15; ++j)
	//		p_Renderer->CreateSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j), glm::vec2(50.0f + i * 30.0f, 50.0f + j * 30.0f), glm::vec2(20.0f, 20.0f), 1);

	p_Renderer->CreateSimpleRenderable("r1", glm::vec2(p_Window->GetWidth()/2, p_Window->GetHeight() / 10), glm::vec2(300.0f, 50.0f), 1);

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			p_Renderer->CreateRenderable3d("3d" + std::to_string(i) + "j" + std::to_string(j), glm::vec3(-900.0f + 300 * i, 450.0f + -300.0f * j, -3000.0f), glm::vec3(70.0f, 70.0f, 70.0f));
			p_Renderer->GetRenderable3d("3d" + std::to_string(i) + "j" + std::to_string(j))->Color = glm::vec4(0.8f, 0.0f, 1.0f, 1.0f);
		}

	}

	//p_Renderer->CreateSimpleRenderable("r3", glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f));
}

void Game::Tick(float fDeltaTime)
{ 	
	p_Renderer->GetSimpleRenderable("r1")->Color = (glm::vec4(col, 1.0f, 0.0f, 1.0f));
	p_Renderer->GetSimpleRenderable("r1")->Position = (glm::vec2(p_Window->GetWidth()/2, p_Window->GetHeight() / 10));

	//p_Renderer->GetRenderable3d("3d")->Rotation.z = rot;
	//p_Renderer->GetRenderable3d("3d")->Position.x += increment * fDeltaTime * 200;

	//p_Renderer->GetSimpleRenderable("r3")->Rotation.z = rot;
	//p_Renderer->GetSimpleRenderable("r1")->ModifyBuffer(glm::vec2(50.0f*col, 25.0f*col), glm::vec2(300.0f, 50.0f), 1);

	for (int i = 0; i < 7; ++i)	
		for (int j = 0; j < 4; ++j)		
			p_Renderer->GetRenderable3d("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.z = rot;		

	//for (int i = 0; i < 30; ++i)
	//	for (int j = 0; j < 15; ++j)
	//		p_Renderer->GetSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j))->Rotation.z += 0.0015f * fDeltaTime;

	if (col > 1.0f)
		increment = -0.0015f;
	else if (col < 0.0f)
		increment = 0.0015f;

	col += increment * fDeltaTime;
	rot += 0.0015f * fDeltaTime;
}
