#pragma once

#include "IO/Window.h"
#include "Libraries/glm/glm.hpp"
#include "Graphics/Renderer.h"

class Engine
{
protected:

	Engine();
	   
	virtual ~Engine() = 0;

	virtual void Begin() = 0;

	virtual void Tick(float fDeltaTime) = 0;

	void Start();

	inline SimpleRenderer* & Renderer() { return p_Renderer; }

	inline const bool IsKeyPressed  (const char & key)    { return p_Window->IsKeyPressed(key); }
	inline const bool IsMouseClicked(const char & button) { return p_Window->IsMouseClicked(button); }
	inline const bool IsFocused()  const& { return p_Window->IsFocused(); }
	inline const int & GetScreenWidth()  const& { return p_Window->GetWidth();  }
	inline const int & GetScreenHeight() const& { return p_Window->GetHeight(); }
	inline const int & GetMouseX() const& { return p_Window->GetMouseX(); }
	inline const int & GetMouseY() const& { return p_Window->GetMouseY(); }
	inline const int & GetMouseOffsetX() const& { return m_nMouseOffsetX; }
	inline const int & GetMouseOffsetY() const& { return m_nMouseOffsetY; }

private:
	SimpleRenderer* p_Renderer;
	Window* p_Window;

	int m_nPreviousMouseX;
	int m_nPreviousMouseY;
	int m_nMouseOffsetX;
	int m_nMouseOffsetY;
};

