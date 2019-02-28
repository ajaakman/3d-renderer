#include "Game.h"

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}
#endif

Game::Game()
{
	Init();
	Loop();
}

Game::~Game()
{	
}

void Game::Init()
{	
}

void Game::Loop()
{
	SimpleRenderable r1( glm::vec2( 0.0f, 0.0f), glm::vec2( 300.0f, 50.0f), 1);
	SimpleRenderable r2( glm::vec2( 480.0f, 170.0f), glm::vec2( 50.0f, 50.0f), 1);
	SimpleRenderable r3( glm::vec2( 0.0f, 0.0f), glm::vec2( 100.0f, 100.0f));	

	float col = 0.0f;
	float rot = 0.0f;
	float increment = 0.02f;
#ifdef EMSCRIPTEN
	std::function<void()> mainLoop = [&]()
#else
	while (p_Window->ShouldNotClose()) 
#endif 
	{
		p_Renderer.Clear();

		r1.SetColor(glm::vec4(col, 1.0f, 0.0f, 1.0f));
		r1.SetPosition(glm::vec2(col*200+380, 270.0f));

		r2.SetColor(glm::vec4(0.0f, 1.0f, col, 1.0f));
		r2.SetRotation(glm::vec3(0.0f, 0.0f, rot));
		r3.SetRotation(glm::vec3(0.0f, 0.0f, rot));

		r1.Draw();
		r2.Draw();
		r3.Draw();

		if (col > 1.0f)
			increment *= -1.0f;
		else if (col < 0.0f)
			increment *= -1.0f;

		col += increment;
		rot += 0.02f;

		p_Window->SwapBuffers();
		p_Window->PollEvents();
	}
#ifdef EMSCRIPTEN
	; emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#endif
}
