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
	float positions[8] = {
			-0.1f, -0.1f,
			 0.1f, -0.1f,
			 0.1f,  0.1f,
			-0.1f,  0.1f,
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	ElementArrayBuffer* p_ElementArrayBuffer;
	VertexArray* p_VertexArray;
	Program* p_Program;
	Buffer* p_Buffer;
};
