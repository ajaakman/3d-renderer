#include "Window.h"

#include <iostream>

#include "../Utility/Error.h"


Window::Window(int width, int height, const char * name)
	: m_nWidth(width), m_nHeight(height), m_Name(name)
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
		
	m_pWindow = glfwCreateWindow(m_nWidth, m_nHeight, m_Name, NULL, NULL);
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
