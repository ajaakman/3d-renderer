#include "Window.h"

#include <iostream>

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
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}

void Window::Draw()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
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
