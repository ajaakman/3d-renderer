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
	const int & GetWidth();
	const int & GetHeight();
private:
	int m_nWidth;
	int m_nHeight;
	const char * m_Name;
	GLFWwindow* m_pWindow;

	friend void WindowSizeCallback(GLFWwindow* window, int width, int height);
};

extern void WindowSizeCallback(GLFWwindow* window, int width, int height);
