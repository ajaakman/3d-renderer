#pragma once

#include "../Libraries/glm/glm.hpp"

class SimpleRenderable
{
public:
	SimpleRenderable(glm::vec2 position, glm::vec2 scale, float rotation = 0, glm::vec4 color = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
	~SimpleRenderable();

	glm::vec2 Position;
	glm::vec2 Scale;
	float Rotation;
	glm::vec4 Color;

};

