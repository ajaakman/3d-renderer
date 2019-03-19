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
	:m_nPreviousMouseX(0), m_nPreviousMouseY(0), m_nMouseOffsetX(0), m_nMouseOffsetY(0)
{
	p_Window = new Window(960, 540, "GLWindow");
	p_Renderer = new SimpleRenderer(p_Window);
}

Engine::~Engine()
{
	delete p_Renderer;
	delete p_Window;
}

void Engine::Start()
{
	int nCount = 0;

	m_nPreviousMouseX = GetMouseX();
	m_nPreviousMouseY = GetMouseY();

	float fTime = 0.f, fFrames = 0.f, fDeltaTime = 0.f, fHighestDelta = 0.f;
	auto previousTime = std::chrono::high_resolution_clock::now(), currentTime = previousTime;

	Begin();
#ifdef EMSCRIPTEN
	std::function<void()> mainLoop = [&]()
#else
	while (p_Window->Open())
#endif 
	{
		currentTime = std::chrono::high_resolution_clock::now();
		p_Window->PollEvents();
		p_Renderer->Clear();
			   
		m_nMouseOffsetX = GetMouseX() - m_nPreviousMouseX;
		m_nMouseOffsetY = GetMouseY() - m_nPreviousMouseY;

		m_nPreviousMouseX = GetMouseX();
		m_nPreviousMouseY = GetMouseY();


		Tick(fDeltaTime);

		p_Renderer->Draw();
		p_Window->SwapBuffers();

		fTime += fDeltaTime;
		fFrames += fDeltaTime;
		++nCount;
		
		if (fDeltaTime > fHighestDelta)
			fHighestDelta = fDeltaTime;

		if (fTime > 1000.f)
		{
			//std::cout << "FPS: " << (int)(1000.f/(fFrames/(float)nCount)) << "  Lowest: " << (int)(1000.f/ fHighestDelta) << "\n";
			fTime -= 1000.f;
			nCount = 0;
			fFrames = 0.f;
			fHighestDelta = 0.f;
		}
		fDeltaTime = std::chrono::duration<float, std::milli>(currentTime - previousTime).count();
		previousTime = currentTime;
	}
#ifdef EMSCRIPTEN
	; emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#endif
}
