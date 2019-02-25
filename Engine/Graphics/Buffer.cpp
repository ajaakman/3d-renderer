#include "Buffer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include "../Utility/Error.h"

Buffer::Buffer(const void * data, unsigned int size)
{
	GL(glGenBuffers(1, &m_BufferID));
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Buffer::~Buffer()
{
	GL(glDeleteBuffers(1, &m_BufferID));
}

void Buffer::Bind() const
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

