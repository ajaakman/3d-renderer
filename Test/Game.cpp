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
	//		p_Renderer->CreateSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j), glm::vec2(50.f + i * 30.f, 50.f + j * 30.f), glm::vec2(20.f, 20.f), 1);

	p_Renderer->CreateSimpleRenderable("r1", glm::vec2(GetWidth() / 2, GetHeight() / 2), glm::vec2(50.f, 50.f));
	p_Renderer->CreateSprite2D("s1", glm::vec2(GetWidth() / 2, GetHeight() / 2), glm::vec2(70.f, 100.f), "Resources/Textures/logo.png");
	p_Renderer->CreateSprite2D("s2", glm::vec2(GetWidth()/2+35, GetHeight()/2+35), glm::vec2(70.f, 70.f), "Resources/Textures/logo1.png");

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			p_Renderer->CreateRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j), glm::vec3(-900.f + 300 * i, 450.f + -300.f * j, -800.f), glm::vec3(70.f, 70.f, 70.f));
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Color = glm::vec4(0.f, 0.2f, 1.f, 1.f);
		}
	}
}

void Game::Tick(float fDeltaTime)
{ 	
	p_Renderer->GetSimpleRenderable("r1")->Color = (glm::vec4(col, 1.f, 0.f, 1.f));
	p_Renderer->GetSimpleRenderable("r1")->Position = (glm::vec2(GetWidth() / 2 + col * 50, GetHeight() / 10));	
	p_Renderer->GetSimpleRenderable("r1")->Rotation = rot;
		
	if (IsKeyPressed('W'))
		p_Renderer->CameraPosition += p_Renderer->CameraRotation * 1.f * fDeltaTime;
	if (IsKeyPressed('S'))
		p_Renderer->CameraPosition -= p_Renderer->CameraRotation * 1.f * fDeltaTime;
	if (IsKeyPressed('D'))
		p_Renderer->CameraRotation.x -= 0.005f * fDeltaTime;
	if (IsKeyPressed('A'))
		p_Renderer->CameraRotation.x += 0.005f * fDeltaTime;
	if (IsKeyPressed('Q'))
		p_Renderer->CameraPosition += (p_Renderer->CameraRotation + glm::vec3(3.14f, 0.f, -1.f)) * 1.f * fDeltaTime;
	if (IsKeyPressed('E'))
		p_Renderer->CameraPosition -= (p_Renderer->CameraRotation + glm::vec3(3.14f, 0.f, -1.f)) * 1.f * fDeltaTime;

	p_Renderer->GetSprite2D("s1")->Color = (glm::vec4(col, 1.f, 0.f, 1.f));
	p_Renderer->GetSprite2D("s2")->Rotation = rot;
	
	if (IsMouseClicked('L'))
		p_Renderer->GetSprite2D("s2")->Position = (glm::vec2(GetMouseX() - p_Renderer->CameraPosition.x, GetMouseY() - p_Renderer->CameraPosition.y));

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 4; ++j)		
		{
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.x = rot/2.f;
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.y = rot/1.7f;
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.z = rot/1.8f;
		}
	}

	//for (int i = 0; i < 30; ++i)
	//	for (int j = 0; j < 15; ++j)
	//		p_Renderer->GetSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j))->Rotation += 0.0015f * fDeltaTime;

	if (col > 1.f)
		increment = -0.0015f;
	else if (col < 0.f)
		increment = 0.0015f;

	if (rot > 3 && !p_Renderer->GetSprite2D("lateload"))
		p_Renderer->CreateSprite2D("lateload", glm::vec2(GetWidth() / 10, GetHeight() / 10), glm::vec2(70.f, 70.f), "Resources/Textures/logo.png");

	col += increment * fDeltaTime;
	rot += 0.0015f * fDeltaTime;
}
