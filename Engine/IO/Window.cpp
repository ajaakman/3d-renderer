#include "Window.h"

#include <iostream>

#include "../Utility/Error.h"


Window::Window(const int & width, const int & height, const char * name)
	: m_nWidth(width), m_nHeight(height), m_Name(name), m_bFocused(false), m_bKeyW(false), m_bKeyA(false), m_bKeyS(false),
	  m_bKeyD(false), m_bKeyQ(false), m_bKeyE(false), m_bMouseR(false), m_bMouseL(false), m_bKeyC(false), m_bKeySpace(false)
{
	if (!glfwInit())
		std::cout << "GLFW Failed To Initialize!" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(m_nWidth, m_nHeight, m_Name, NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		std::cout << "No Window. GLFW Terminating..." << std::endl;
	}	

	int nFrameBufferWidth, nFrameBufferHeight;
	glfwGetFramebufferSize(m_pWindow, &nFrameBufferWidth, &nFrameBufferHeight);
	glViewport(0, 0, nFrameBufferWidth, nFrameBufferHeight);

	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetWindowSizeCallback(m_pWindow, WindowSizeCallback); 
	glfwSetKeyCallback(m_pWindow, KeyCallback);
	glfwSetCursorPosCallback(m_pWindow, CursorCallback);
	glfwSetMouseButtonCallback(m_pWindow, MouseClickCallback);
	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPos(m_pWindow, m_nWidth/2, m_nHeight/2);		
	glfwMakeContextCurrent(m_pWindow);
#ifndef EMSCRIPTEN
	glewExperimental = GL_TRUE;
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

void Window::SetFocus()
{
	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

bool Window::Open()
{
	return !glfwWindowShouldClose(m_pWindow);
}

const bool Window::IsKeyPressed(const char& key)
{
	if (key == 'W' || key == 'w')
		return m_bKeyW;
	else if (key == 'A' || key == 'a')
		return m_bKeyA;
	else if (key == 'S' || key == 's')
		return m_bKeyS;
	else if (key == 'D' || key == 'd')
		return m_bKeyD;
	else if (key == 'Q' || key == 'q')
		return m_bKeyQ;
	else if (key == 'E' || key == 'e')
		return m_bKeyE;
	else if (key == 'C' || key == 'c')
		return m_bKeyC;
	else if (key == ' ')
		return m_bKeySpace;
	std::cout << "Error: Invalid key input binding!\n";
	return false;
}

const bool Window::IsMouseClicked(const char & button)
{
	if (button == 'L' || button == 'l' || button == '1')
		return m_bMouseL;
	else if (button == 'R' || button == 'r' || button == '2')
		return m_bMouseR;
	std::cout << "Error: Invalid mouse input binding!\n";
	return false;
}

const bool Window::IsFocused()
{
	return m_bFocused;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
	w->m_nWidth = width;
	w->m_nHeight = height;

	int nFrameBufferWidth, nFrameBufferHeight;
	glfwGetFramebufferSize(w->m_pWindow, &nFrameBufferWidth, &nFrameBufferHeight);
	glViewport(0, 0, nFrameBufferWidth, nFrameBufferHeight);
}

void CursorCallback(GLFWwindow* window, double xpos, double ypos)
{	
	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
	w->m_nMousePosX = (int)xpos;
	int v = ((int)ypos - w->m_nHeight);
	int const mask = v >> (sizeof(int) * CHAR_BIT - 1);
	int r = (v + mask) ^ mask;
	w->m_nMousePosY = r;
}

void MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	w->m_bFocused = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		w->m_bMouseR = true;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		w->m_bMouseR = false;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		w->m_bMouseL = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		w->m_bMouseL = false;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_W && action == GLFW_PRESS)	
		w->m_bKeyW = true;	
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)	
		w->m_bKeyW = false;
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
		w->m_bKeyA = true;
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		w->m_bKeyA = false;
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		w->m_bKeyS = true;
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		w->m_bKeyS = false;
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		w->m_bKeyD = true;
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		w->m_bKeyD = false;
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		w->m_bKeyQ = true;
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		w->m_bKeyQ = false;
	else if (key == GLFW_KEY_E && action == GLFW_PRESS)
		w->m_bKeyE = true;
	else if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		w->m_bKeyE = false;
	else if (key == GLFW_KEY_C && action == GLFW_PRESS)
		w->m_bKeyC = true;
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE)
		w->m_bKeyC = false;
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		w->m_bKeySpace = true;
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		w->m_bKeySpace = false;
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		w->m_bFocused = false;
	}
}