#pragma once

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#else
#include <GL/glew.h>
#endif

#include "GLFW/glfw3.h"

class Window
{
public:
	Window();
	~Window();

	void SwapBuffers();
	void PollEvents();
	bool ShouldNotClose();
private:
	int Init();
	GLFWwindow* m_pWindow;
};

