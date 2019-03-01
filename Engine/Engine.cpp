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
	int nCount = 0, nBuff = 0;
	float fTime = 0.0f, fFrames = 0.0f, fDeltaTime = 0.0f, fHighestDelta = 0.0f;
	auto previousTime = std::chrono::high_resolution_clock::now(), currentTime = previousTime;
#ifdef EMSCRIPTEN
	std::function<void()> mainLoop = [&]()
#else
	while (p_Window->ShouldNotClose())
#endif 
	{
		currentTime = std::chrono::high_resolution_clock::now();

		p_Renderer->Clear();

		Tick(fDeltaTime);

		p_Renderer->Draw();
		p_Window->SwapBuffers();
		p_Window->PollEvents();

		fTime += fDeltaTime;
		fFrames += fDeltaTime;
		++nCount;
		
		if (fDeltaTime > fHighestDelta)
			fHighestDelta = fDeltaTime;

		if (fTime > 1000.0f)
		{
			std::cout << "FPS: " << (int)(1000.0f/(fFrames/(float)nCount)) << "  Lowest: " << (int)(1000.0f/ fHighestDelta) << "\n";
			fTime -= 1000.0f;
			nCount = 0;
			fFrames = 0.0f;
			fHighestDelta = 0.0f;
		}
		fDeltaTime = std::chrono::duration<float, std::milli>(currentTime - previousTime).count();
		previousTime = currentTime;
	}
#ifdef EMSCRIPTEN
	; emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#endif
}
