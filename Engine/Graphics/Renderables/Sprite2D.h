#pragma once

#include "../../Libraries/glm/glm.hpp"

class Sprite2D
{
public:
	Sprite2D(glm::vec2 position, glm::vec2 scale, float rotation = 0.0f, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	~Sprite2D();

	glm::vec2 Position;
	glm::vec2 Scale;
	float Rotation;
	glm::vec4 Color;	
};

