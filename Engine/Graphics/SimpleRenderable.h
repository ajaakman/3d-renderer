#pragma once

#include "ElementArrayBuffer.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Program.h"

class SimpleRenderable
{
public:
	SimpleRenderable(float positionX, float positionY, float sizeX, float sizeY, int centered = 0);
	~SimpleRenderable();

	void SetColor(float r, float b, float g, float a);
	void Draw();
private:

	ElementArrayBuffer* p_ElementArrayBuffer;
	VertexArray* p_VertexArray;
	Program* p_Program;
	Buffer* p_Buffer;
};

