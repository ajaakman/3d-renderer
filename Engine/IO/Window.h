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
	Window(int width, int height, const char * name);
	~Window();

	void SwapBuffers();
	void PollEvents();
	bool ShouldNotClose();
private:
	int m_nWidth;
	int m_nHeight;
	const char * m_Name;
	GLFWwindow* m_pWindow;
};

