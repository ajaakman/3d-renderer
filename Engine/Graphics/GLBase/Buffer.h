#pragma once

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include "../Vertex.h"

class Buffer
{
public:
	Buffer(const void* data, unsigned int size, const Vertex & vertex, GLenum usage);
	~Buffer();

	void ModifyBuffer(const void * data, int offset, unsigned int size);

	void Bind() const;
private:
	unsigned int m_BufferID;
	unsigned int m_ArrayID;
};

