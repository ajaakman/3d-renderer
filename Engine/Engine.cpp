#include "Engine.h"

#include <iostream>
#include <chrono>

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}
#endif

Engine::Engine()
{
	p_Window = new Window(960, 540, "GLWindow");
	p_Renderer = new Renderer;
}

Engine::~Engine()
{
	delete p_Window;
	delete p_Renderer;
}

void Engine::Loop()
{
	double time = 0.0;
	auto previousTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	double deltaTime = 0.0;
#ifdef EMSCRIPTEN
	std::function<void()> mainLoop = [&]()
#else
	while (p_Window->ShouldNotClose())
#endif 
	{
		currentTime = std::chrono::high_resolution_clock::now();

		p_Renderer->Clear();

		Tick(deltaTime);

		p_Renderer->Draw();
		p_Window->SwapBuffers();
		p_Window->PollEvents();

		time += deltaTime;
		if (time > 1000.0)
		{
			std::cout << "FPS: " << (int)(1000.0/deltaTime) << "\n";
			time -= 1000.0;
		}
		deltaTime = std::chrono::duration<double, std::milli>(currentTime - previousTime).count();
		previousTime = currentTime;
	}
#ifdef EMSCRIPTEN
	; emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#endif
}
