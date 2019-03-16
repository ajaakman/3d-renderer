#include "Game.h"
#include <iostream>

Game::Game()
{	
	Start();
}

Game::~Game()
{	
}

void Game::Begin()
{		
	for (unsigned i = 0; i < 7; ++i)	
		for (unsigned j = 0; j < 4; ++j)		
			p_Boxes.push_back(Renderer()->Create(Mesh::CUBE, glm::vec3(-900.f + 300 * i, 450.f + -300.f * j, -800.f), glm::vec3(140.f, 140.f, 140.f), "Resources/Textures/box.png", "Resources/Textures/boxs.png"));
	
	p_Box = Renderer()->Create(Mesh::CUBE, glm::vec3(0.f, 0.f, -200.f), glm::vec3(70.f, 70.f, 70.f), "Resources/Textures/box.png", "Resources/Textures/boxs.png");

	Renderer()->Create(Mesh::SPRITE, glm::vec3(100.f, 100.f, 0.f), glm::vec3(70.f, 70.f, 0.f), "Resources/Textures/test.png", "");
	Renderer()->Create(Mesh::SPRITE, glm::vec3(120.f, 120.f, 0.f), glm::vec3(70.f, 70.f, 0.f), "Resources/Textures/test.png", "");
}

void Game::Tick(float fDeltaTime)
{ 			
	if (IsKeyPressed('W'))
	{
		Renderer()->GetCamera2D()->Move(fDeltaTime, Camera::UP);
		Renderer()->GetCamera3D()->Move(fDeltaTime, Camera::FORWARD);
	}
	if (IsKeyPressed('S'))
	{
		Renderer()->GetCamera2D()->Move(fDeltaTime, Camera::DOWN);
		Renderer()->GetCamera3D()->Move(fDeltaTime, Camera::BACK);
	}
	if (IsKeyPressed('A'))
	{
		Renderer()->GetCamera2D()->Move(fDeltaTime, Camera::LEFT);
		Renderer()->GetCamera3D()->Move(fDeltaTime, Camera::LEFT);
	}
	if (IsKeyPressed('D'))
	{
		Renderer()->GetCamera2D()->Move(fDeltaTime, Camera::RIGHT);
		Renderer()->GetCamera3D()->Move(fDeltaTime, Camera::RIGHT);
	}
	
	if (IsFocused())
		Renderer()->GetCamera3D()->Rotate(fDeltaTime, GetMouseOffsetX(), GetMouseOffsetY());

	p_Box->Rotation.x = linear;
	p_Box->Rotation.y = linear /1.3f;
	
	for (auto & box : p_Boxes)
	{
		box->Rotation.x = linear /2.f;
		box->Rotation.y = linear /1.7f;
		box->Rotation.z = linear /1.8f;
		box->Color = (glm::vec4(pendulum, 1.f, 0.f, 1.f));
	}		

	if (pendulum > 1.f)
		increment = -0.0015f;
	else if (pendulum < 0.f)
		increment = 0.0015f;

	if (linear > 3 && !created)
	{
		Renderer()->Create(Mesh::CUBE, glm::vec3(GetWidth() / 10, GetHeight() / 10, -200.f), glm::vec3(70.f, 70.f, 0.f), "Resources/Textures/test.png", "");
		created = true;
	}

	pendulum += increment * fDeltaTime;
	linear += 0.0015f * fDeltaTime;
}
