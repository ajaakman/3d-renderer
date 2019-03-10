#include "ElementArrayBuffer.h"

#include "../../Utility/Error.h"

ElementArrayBuffer::ElementArrayBuffer(const unsigned * data, unsigned count, GLenum usage)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned) == sizeof(GLuint));

	GL(glGenBuffers(1, &m_ArrayBufferID));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ArrayBufferID));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, usage));
}

ElementArrayBuffer::~ElementArrayBuffer()
{
	GL(glDeleteBuffers(1, &m_ArrayBufferID));
}

void ElementArrayBuffer::Bind() const
{
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ArrayBufferID));
}

unsigned ElementArrayBuffer::GetCount() const 
{ 
	return m_Count; 
}