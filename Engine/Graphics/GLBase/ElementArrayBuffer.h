#pragma once

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

class ElementArrayBuffer
{
private:
	unsigned int m_ArrayBufferID;
	unsigned int m_Count;
public:
	ElementArrayBuffer(const unsigned int* data, unsigned int count, GLenum usage);
	~ElementArrayBuffer();

	void Bind() const;

	unsigned int GetCount() const;
};

