#include "Vertex.h"


Vertex::Vertex()
	: m_Stride(0) {}

void Vertex::PushFloat(unsigned int count)
{
	m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
	m_Stride += count * VertexElement::GetSizeOfType(GL_FLOAT);
}

void Vertex::PushUInt(unsigned int count)
{
	m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
	m_Stride += count * VertexElement::GetSizeOfType(GL_UNSIGNED_INT);
}

void Vertex::PushChar(unsigned int count)
{
	m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
	m_Stride += count * VertexElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

const std::vector<Vertex::VertexElement> Vertex::GetElements() const& { return m_Elements; }
unsigned int Vertex::GetStride() const { return m_Stride; }
