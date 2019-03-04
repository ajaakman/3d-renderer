#pragma once

#include "GLBase/ElementArrayBuffer.h"
#include "GLBase/Buffer.h"
#include "GLBase/Program.h"

#include "../Libraries/glm/glm.hpp"

class SimpleRenderable
{
public:
	SimpleRenderable(glm::vec2 position, glm::vec2 scale, int centered = 0);
	~SimpleRenderable();

	void Draw(const glm::mat4 & view_projection);

	glm::vec2 Position;
	glm::vec2 Scale;
	glm::vec4 Color;
	float Rotation;

	void ModifyBuffer(glm::vec2 position, glm::vec2 size, int centered);
private:
	ElementArrayBuffer* p_ElementArrayBuffer;
	Program* p_Program;
	Buffer* p_Buffer;
};

