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
	bool Open();

	inline const int & GetWidth()   { return m_nWidth; }
	inline const int & GetHeight()  { return m_nHeight;}
	const bool & IsKeyPressed(const char& key);
private:
	int m_nWidth;
	int m_nHeight;
	const char * m_Name;
	GLFWwindow* m_pWindow;

	bool m_bKeyW;
	bool m_bKeyA;
	bool m_bKeyS;
	bool m_bKeyD;

	friend void WindowSizeCallback(GLFWwindow* window, int width, int height);
	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

extern void WindowSizeCallback(GLFWwindow* window, int width, int height);
extern void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);