#pragma once

#include "GLBase/ElementArrayBuffer.h"
#include "GLBase/Buffer.h"
#include "GLBase/Program.h"

#include "../Libraries/glm/glm.hpp"

class Renderable3d
{
public:
	Renderable3d(glm::vec3 position, glm::vec3 scale);
	~Renderable3d();

	void Draw(const glm::mat4 & view_projection);

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;
	glm::vec4 Color;

private:
	ElementArrayBuffer* p_ElementArrayBuffer;
	Program* p_Program;
	Buffer* p_Buffer;
};

