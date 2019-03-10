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
	unsigned m_ArrayBufferID;
	unsigned m_Count;
public:
	ElementArrayBuffer(const unsigned* data, unsigned count, GLenum usage);
	~ElementArrayBuffer();

	void Bind() const;

	unsigned GetCount() const;
};

