#include "Engine.h"

Engine::Engine()
{
	p_Window = new Window();
	p_Renderer = new Renderer();
}

Engine::~Engine()
{
	delete p_Window;
	delete p_Renderer;
}
