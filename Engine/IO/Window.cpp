#include "Window.h"

#include <iostream>

#include "../Utility/Error.h"


Window::Window(int width, int height, const char * name)
	: m_nWidth(width), m_nHeight(height), m_Name(name)
{
	if (!glfwInit())
		std::cout << "GLFW Failed To Initialize!" << std::endl;

	m_pWindow = glfwCreateWindow(m_nWidth, m_nHeight, m_Name, NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		std::cout << "No Window. GLFW Terminating..." << std::endl;
	}	

	glfwSetWindowUserPointer(m_pWindow, this);

	glfwSetWindowSizeCallback(m_pWindow, WindowSizeCallback);

	glfwMakeContextCurrent(m_pWindow);
#ifndef EMSCRIPTEN
	GLenum error = glewInit();
	if (error != GLEW_OK)
		std::cout << "GLEW Failed to Initialize!" << std::endl;
#endif
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSwapInterval(0); // VSync
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

const int & Window::GetWidth()
{
	return m_nWidth;
}

const int & Window::GetHeight()
{
	return m_nHeight;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->m_nWidth = width;
	static_cast<Window*>(glfwGetWindowUserPointer(window))->m_nHeight = height;
}
