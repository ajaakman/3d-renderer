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
	for (unsigned i = 0; i < 7; ++i)	
		for (unsigned j = 0; j < 4; ++j)		
			p_Renderer->Create("3d" + std::to_string(i) + "_" + std::to_string(j), glm::vec3(-900.f + 300 * i, 450.f + -300.f * j, -800.f), glm::vec3(140.f, 140.f, 140.f), "Resources/Textures/test.png", "r");
	
	p_Renderer->Create("r", glm::vec3(0.f, 0.f, -200.f), glm::vec3(70.f, 70.f, 70.f), "Resources/Textures/test1.png", "r");

	p_Renderer->CreateS("s", glm::vec3(100.f, 100.f, 0.f), glm::vec3(70.f, 70.f, 0.f), "Resources/Textures/test.png", "r");
}

void Game::Tick(float fDeltaTime)
{ 			
	if (IsKeyPressed('W'))
		p_Renderer->CameraPosition += p_Renderer->CameraRotation * 0.2f * fDeltaTime;
	if (IsKeyPressed('S'))
		p_Renderer->CameraPosition -= p_Renderer->CameraRotation * 0.2f * fDeltaTime;
	if (IsKeyPressed('D'))
		p_Renderer->CameraRotation.x -= 0.001f * fDeltaTime;
	if (IsKeyPressed('A'))
		p_Renderer->CameraRotation.x += 0.001f * fDeltaTime;
	if (IsKeyPressed('Q'))
		p_Renderer->CameraPosition += (p_Renderer->CameraRotation + glm::vec3(3.14f, 0.f, -1.f)) * 0.2f * fDeltaTime;
	if (IsKeyPressed('E'))
		p_Renderer->CameraPosition -= (p_Renderer->CameraRotation + glm::vec3(3.14f, 0.f, -1.f)) * 0.2f * fDeltaTime;

	p_Renderer->Find("r")->Rotation.x = linear;
	p_Renderer->Find("r")->Rotation.y = linear /1.3f;
	
	if (IsMouseClicked('L'))
		p_Renderer->Find("r")->Position = (glm::vec3(p_Renderer->CameraPosition.x - GetMouseX() + GetWidth()/2, p_Renderer->CameraPosition.y - GetMouseY() + GetHeight() / 2, -200.f));

	for (unsigned i = 0; i < 7; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
		{
			p_Renderer->Find("3d" + std::to_string(i) + "_" + std::to_string(j))->Rotation.x = linear /2.f;
			p_Renderer->Find("3d" + std::to_string(i) + "_" + std::to_string(j))->Rotation.y = linear /1.7f;
			p_Renderer->Find("3d" + std::to_string(i) + "_" + std::to_string(j))->Rotation.z = linear /1.8f;
			p_Renderer->Find("3d" + std::to_string(i) + "_" + std::to_string(j))->Color = (glm::vec4(pendulum, 1.f, 0.f, 1.f));
		}
	}

	if (pendulum > 1.f)
		increment = -0.0015f;
	else if (pendulum < 0.f)
		increment = 0.0015f;

	if (linear > 3 && !p_Renderer->Find("rl"))
		p_Renderer->Create("rl", glm::vec3(GetWidth() / 10, GetHeight() / 10, -200.f), glm::vec3(70.f, 70.f, 0.f), "Resources/Textures/test.png", "r");

	pendulum += increment * fDeltaTime;
	linear += 0.0015f * fDeltaTime;
}
