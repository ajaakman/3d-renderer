#pragma once

#include "../../Libraries/glm/glm.hpp"

#include "../GLBase/Texture.h"

class Sprite2D
{
public:
	Sprite2D(glm::vec2 position, glm::vec2 scale, std::string path, float rotation = 0.f, glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f));
	Sprite2D(glm::vec2 position, glm::vec2 scale, float rotation = 0.f, glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f));
	~Sprite2D();

	glm::vec2 Position;
	glm::vec2 Scale;
	float Rotation;
	glm::vec4 Color;

	Texture* Texture;
};

