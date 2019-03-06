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

	p_Renderer->CreateSimpleRenderable("r1", glm::vec2(GetWidth() / 2, GetHeight() / 2), glm::vec2(50.0f, 50.0f));
	p_Renderer->CreateSprite2D("s1", glm::vec2(GetWidth() / 2, GetHeight() / 2), glm::vec2(70.0f, 100.0f), "Resources/Textures/logo.png");
	p_Renderer->CreateSprite2D("s2", glm::vec2(GetWidth()/2+35, GetHeight()/2+35), glm::vec2(70.0f, 70.0f), "Resources/Textures/logo1.png");

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			p_Renderer->CreateRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j), glm::vec3(-900.0f + 300 * i, 450.0f + -300.0f * j, -3000.0f), glm::vec3(70.0f, 70.0f, 70.0f));
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Color = glm::vec4(0.0f, 0.2f, 1.0f, 1.0f);
		}
	}
}

void Game::Tick(float fDeltaTime)
{ 	
	p_Renderer->GetSimpleRenderable("r1")->Color = (glm::vec4(col, 1.0f, 0.0f, 1.0f));
	p_Renderer->GetSimpleRenderable("r1")->Position = (glm::vec2(GetWidth() / 2 + col * 50, GetHeight() / 10));	
	p_Renderer->GetSimpleRenderable("r1")->Rotation = rot;
		
	if (KeyPressed('W'))
		p_Renderer->GetSprite2D("s1")->Position.y += 0.15f * fDeltaTime;
	if (KeyPressed('S'))
		p_Renderer->GetSprite2D("s1")->Position.y -= 0.15f * fDeltaTime;
	if (KeyPressed('D'))
		p_Renderer->GetSprite2D("s1")->Position.x += 0.15f * fDeltaTime;
	if (KeyPressed('A'))
		p_Renderer->GetSprite2D("s1")->Position.x -= 0.15f * fDeltaTime;

	p_Renderer->GetSprite2D("s1")->Color = (glm::vec4(col, 1.0f, 0.0f, 1.0f));
	
	if (MouseClicked('L'))
		p_Renderer->GetSprite2D("s2")->Position = (glm::vec2(MouseX(), MouseY()));

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 4; ++j)		
		{
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.x = rot/2.0f;
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.y = rot/1.7f;
			p_Renderer->GetRenderable3D("3d" + std::to_string(i) + "j" + std::to_string(j))->Rotation.z = rot/1.8f;
		}
	}

	//for (int i = 0; i < 30; ++i)
	//	for (int j = 0; j < 15; ++j)
	//		p_Renderer->GetSimpleRenderable("rend" + std::to_string(i) + "j" + std::to_string(j))->Rotation += 0.0015f * fDeltaTime;

	if (col > 1.0f)
		increment = -0.0015f;
	else if (col < 0.0f)
		increment = 0.0015f;

	if (rot > 3 && !p_Renderer->GetSprite2D("lateload"))
		p_Renderer->CreateSprite2D("lateload", glm::vec2(GetWidth() / 10, GetHeight() / 10), glm::vec2(70.0f, 70.0f), "Resources/Textures/logo.png");

	col += increment * fDeltaTime;
	rot += 0.0015f * fDeltaTime;
}
