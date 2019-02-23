#include "Game.h"

#include "../Engine/Graphics/ElementArrayBuffer.h"
#include "../Engine/Graphics/Buffer.h"
#include "../Engine/Graphics/VertexArray.h"
#include "../Engine/Graphics/Program.h"

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
	float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f, 0.5f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	Buffer buffer(positions, 4 * 2 * sizeof(float));

	Vertex vertex;
	vertex.PushFloat(2);
	va.AddBuffer(buffer, vertex);

	ElementArrayBuffer ib(indices, 6);

	Program shader("Resources/Shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.8f, 0.4f, 0.8f, 1.0f);

	float r = 0.0f;
	float increment = 0.05f;
	while (window->ShouldNotClose()) 
	{
		window->Clear();

		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.4f, 0.8f, 1.0f);

		va.Bind();
		ib.Bind();

		window->Draw();

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;

		window->SwapBuffers();
		window->PollEvents();
	}
}
