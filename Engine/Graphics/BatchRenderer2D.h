#pragma once

#include "../IO/Window.h"

class BatchRenderer2D
{
public:
	BatchRenderer2D(Window* window);
	~BatchRenderer2D();
	
	Window* m_pWindow;
};
