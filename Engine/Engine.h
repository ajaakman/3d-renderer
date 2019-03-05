#pragma once

#include "IO/Window.h"
#include "Libraries/glm/glm.hpp"
#include "Graphics/Renderer.h"

class Engine
{
public:

	Engine();

	Window* p_Window;
	Renderer* p_Renderer;

	virtual ~Engine() = 0;

	virtual void Begin() = 0;

	virtual void Tick(float fDeltaTime) = 0;

	void Loop();
};

