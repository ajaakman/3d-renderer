#include "Window.h"

#include <iostream>

#include "../Utility/Error.h"


Window::Window()
{
	Init();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

bool Window::ShouldNotClose()
{
	return !glfwWindowShouldClose(m_pWindow);
}

int Window::Init()
{
	if (!glfwInit())
		return -1;
		
	m_pWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_pWindow);
#ifndef EMSCRIPTEN
	GLenum error = glewInit();
	if (error != GLEW_OK)
		std::cout << "Error!" << std::endl;
#endif
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSwapInterval(1); // VSync
	return 0;
}
