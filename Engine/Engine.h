#pragma once
#include "IO/Window.h"
#include "Graphics/SimpleRenderable.h"

class Engine
{
public:

	Engine();

	Window* window;

	virtual ~Engine() = 0;

	virtual void Init() = 0;

	virtual void Loop() = 0;
};
