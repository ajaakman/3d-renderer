#include "Engine.h"

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
#ifdef EMSCRIPTEN
	std::function<void()> mainLoop = [&]()
#else
	while (p_Window->ShouldNotClose())
#endif 
	{
		p_Renderer->Clear();

		Tick();

		p_Renderer->Draw();
		p_Window->SwapBuffers();
		p_Window->PollEvents();
	}
#ifdef EMSCRIPTEN
	; emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#endif
}
