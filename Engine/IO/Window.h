#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window();
	~Window();

	void Clear();
	void SwapBuffers();
	void PollEvents();
	bool ShouldNotClose();
private:
	int Init();
	GLFWwindow* m_pWindow;
};

