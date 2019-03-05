#include "Renderable3d.h"

Renderable3D::Renderable3D(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::vec4 color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color)
{		
}

Renderable3D::~Renderable3D()
{
}

