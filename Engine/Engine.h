#pragma once

#include "IO/Window.h"
#include "Libraries/glm/glm.hpp"
#include "Graphics/BatchRenderer2D.h"
#include "Graphics/Renderer.h"
#include "Graphics/SimpleRenderable.h"

class Engine
{
public:

	Engine();

	Window* p_Window;
	Renderer* p_Renderer;

	virtual ~Engine() = 0;

	virtual void Begin() = 0;

	virtual void Tick(double deltaTime) = 0;

	void Loop();
};

