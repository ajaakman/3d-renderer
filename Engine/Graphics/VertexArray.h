#pragma once

#include "Buffer.h"
#include "Vertex.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const Buffer& buffer, const Vertex& vertex);

	void Bind() const;
private:
	unsigned int m_ArrayID;
};

