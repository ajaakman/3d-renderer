#pragma once

#include "../../Libraries/glm/glm.hpp"

class Renderable3D
{
public:
	Renderable3D(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), glm::vec4 color = glm::vec4(0.9f, 0.9f, 0.9f, 1.f));
	~Renderable3D();
	
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;
	glm::vec4 Color;
};

