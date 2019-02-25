#include "VertexArray.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include "../Utility/Error.h"


VertexArray::VertexArray()
{
	GL(glGenVertexArrays(1, &m_ArrayID));
}

VertexArray::~VertexArray()
{
	GL(glDeleteVertexArrays(1, &m_ArrayID));
}

void VertexArray::AddBuffer(const Buffer & buffer, const Vertex & vertex)
{
	Bind();
	buffer.Bind();
	const auto& elements = vertex.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GL(glEnableVertexAttribArray(i));
		GL(glVertexAttribPointer(i, element.count, element.type, element.normalized, vertex.GetStride(), (const void*)offset));
		offset += element.count * Vertex::VertexElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GL(glBindVertexArray(m_ArrayID));
}
