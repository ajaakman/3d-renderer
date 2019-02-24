#pragma once
#include "ElementArrayBuffer.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Program.h"

class SimpleRenderable
{
public:
	SimpleRenderable(float positionX);
	~SimpleRenderable();

	void UpdateUniforms(float color);
	void Draw();
private:

	ElementArrayBuffer* p_ElementArrayBuffer;
	VertexArray* p_VertexArray;
	Program* p_Program;
	Buffer* p_Buffer;
};

