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
	Buffer(const void* data, unsigned size, const VertexLayout & vertex, GLenum usage);
	~Buffer();

	void ModifyBuffer(const void * data, int offset, unsigned size);

	void Bind() const;
private:
	unsigned m_BufferID;
	unsigned m_ArrayID;
};

