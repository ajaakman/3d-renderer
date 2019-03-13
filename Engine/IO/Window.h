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

	inline const int & GetMouseX() { return m_nMousePosX; }
	inline const int & GetMouseY() { return m_nMousePosY; }

	const bool IsKeyPressed(const char& key);
	const bool IsMouseClicked(const char& button);
	const bool IsFocused();

	void SetFocus();
private:
	int m_nWidth;
	int m_nHeight;
	const char * m_Name;
	GLFWwindow* m_pWindow;

	bool m_bFocused;
	bool m_bKeyW;
	bool m_bKeyA;
	bool m_bKeyS;
	bool m_bKeyD;
	bool m_bKeyQ;
	bool m_bKeyE;
	bool m_bKeyC;
	bool m_bKeySpace;
	bool m_bMouseL;
	bool m_bMouseR;
	int m_nMousePosX;
	int m_nMousePosY;

	friend void WindowSizeCallback(GLFWwindow* window, int width, int height);
	friend void CursorCallback(GLFWwindow* window, double xpos, double ypos);
	friend void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

extern void WindowSizeCallback(GLFWwindow* window, int width, int height);
extern void CursorCallback(GLFWwindow* window, double xpos, double ypos);
extern void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
extern void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);