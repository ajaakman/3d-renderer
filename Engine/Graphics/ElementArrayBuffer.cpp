#include "ElementArrayBuffer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include "../Utility/Error.h"

ElementArrayBuffer::ElementArrayBuffer(const unsigned int * data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GL(glGenBuffers(1, &m_ArrayBufferID));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ArrayBufferID));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

ElementArrayBuffer::~ElementArrayBuffer()
{
	GL(glDeleteBuffers(1, &m_ArrayBufferID));
}

void ElementArrayBuffer::Bind() const
{
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ArrayBufferID));
}

unsigned int ElementArrayBuffer::GetCount() const 
{ 
	return m_Count; 
}