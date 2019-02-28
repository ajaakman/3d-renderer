#include "Engine.h"

Engine::Engine()
{
	p_Window = new Window(960, 540, "GLWindow");
}

Engine::~Engine()
{
	delete p_Window;
}
