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

void Window::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}

void Window::Draw()
{
	GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
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

	GLenum error = glewInit();
	if (error != GLEW_OK)
		std::cout << "Error!" << std::endl;

	glfwSwapInterval(1); // VSync

	std::cout << glGetString(GL_VERSION) << std::endl;
	return 0;
}
