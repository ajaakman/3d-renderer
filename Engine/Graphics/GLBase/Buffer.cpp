#include "Buffer.h"

#include "../../Utility/Error.h"

Buffer::Buffer(const void * data, unsigned int size, GLenum usage)
{
	GL(glGenBuffers(1, &m_BufferID));
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

Buffer::~Buffer()
{
	GL(glDeleteBuffers(1, &m_BufferID));
}

void Buffer::Bind() const
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

