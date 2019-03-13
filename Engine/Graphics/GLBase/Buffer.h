#pragma once

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include "../GUtility/VertexLayout.h"

class Buffer
{
public:
	Buffer(const void* data, const unsigned & size, const VertexLayout & vertex, const GLenum & usage);
	~Buffer();

	void ModifyBuffer(const void * data, const int & offset, const unsigned & size);

	void Bind() const;
private:
	unsigned m_BufferID;
	unsigned m_ArrayID;
};

