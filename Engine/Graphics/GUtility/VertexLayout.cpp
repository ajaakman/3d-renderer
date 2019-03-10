#include "VertexLayout.h"

VertexLayout::VertexLayout()
	: m_Stride(0) {}

void VertexLayout::PushFloat(unsigned count)
{
	m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
	m_Stride += count * VertexElement::GetSizeOfType(GL_FLOAT);
}

void VertexLayout::PushUInt(unsigned count)
{
	m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
	m_Stride += count * VertexElement::GetSizeOfType(GL_UNSIGNED_INT);
}

void VertexLayout::PushChar(unsigned count)
{
	m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
	m_Stride += count * VertexElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

const std::vector<VertexLayout::VertexElement> VertexLayout::GetElements() const& { return m_Elements; }
unsigned VertexLayout::GetStride() const { return m_Stride; }
