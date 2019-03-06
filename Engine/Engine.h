#pragma once

#include "IO/Window.h"
#include "Libraries/glm/glm.hpp"
#include "Graphics/Renderer.h"

class Engine
{
protected:

	Engine();

	Renderer* p_Renderer;


	virtual ~Engine() = 0;

	virtual void Begin() = 0;

	virtual void Tick(float fDeltaTime) = 0;

	void Loop();

	inline const bool IsKeyPressed   (const char & key)    { return p_Window->IsKeyPressed(key); }
	inline const bool IsMouseClicked (const char & button) { return p_Window->IsMouseClicked(button); }
	inline const int & GetWidth()    { return p_Window->GetWidth();  }
	inline const int & GetHeight()   { return p_Window->GetHeight(); }
	inline const int & GetMouseX()      { return p_Window->GetMouseX(); }
	inline const int & GetMouseY()      { return p_Window->GetMouseY(); }

private:
	Window* p_Window;
};

