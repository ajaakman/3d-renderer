#pragma once

#include "GLBase/ElementArrayBuffer.h"
#include "GLBase/Buffer.h"
#include "GLBase/VertexArray.h"
#include "GLBase/Program.h"
#include "../Libraries/glm/glm.hpp"

class SimpleRenderable
{
public:
	SimpleRenderable(glm::vec2 position, glm::vec2 size, int centered = 0);
	~SimpleRenderable();

	void SetColor(glm::vec4 color);
	void SetPosition(glm::vec2 position);
	void Draw();
private:

	ElementArrayBuffer* p_ElementArrayBuffer;
	VertexArray* p_VertexArray;
	Program* p_Program;
	Buffer* p_Buffer;
};

