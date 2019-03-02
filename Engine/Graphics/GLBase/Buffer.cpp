#include "Buffer.h"

#include "../../Utility/Error.h"

Buffer::Buffer(const void * data, unsigned int size, const Vertex & vertex, GLenum usage)
{
	GL(glGenVertexArrays(1, &m_ArrayID));
	GL(glBindVertexArray(m_ArrayID));

	GL(glGenBuffers(1, &m_BufferID));
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	
	const auto& elements = vertex.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GL(glEnableVertexAttribArray(i));
		GL(glVertexAttribPointer(i, element.count, element.type, element.normalized, vertex.GetStride(), (const void*)offset));
		offset += element.count * Vertex::VertexElement::GetSizeOfType(element.type);
	}

	GL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

Buffer::~Buffer()
{
	GL(glDeleteBuffers(1, &m_BufferID));
	GL(glDeleteVertexArrays(1, &m_ArrayID));
}

void Buffer::Bind() const
{
	GL(glBindVertexArray(m_ArrayID));
}

void Buffer::ModifyBuffer(const void * data, int offset, unsigned int size)
{
	GL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}
