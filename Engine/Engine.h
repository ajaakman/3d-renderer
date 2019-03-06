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

	inline const bool KeyPressed  (const char & key)    { return p_Window->IsKeyPressed(key); }
	inline const bool MouseClicked(const char & button) { return p_Window->IsMouseClicked(button); }
	inline const int & GetWidth()    { return p_Window->GetWidth();  }
	inline const int & GetHeight()   { return p_Window->GetHeight(); }
	inline const int & MouseX()      { return p_Window->GetMouseX(); }
	inline const int & MouseY()      { return p_Window->GetMouseY(); }

private:
	Window* p_Window;
};

