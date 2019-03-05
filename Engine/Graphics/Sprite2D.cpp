#include "Sprite2D.h"

Sprite2D::Sprite2D(glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color)
{	
}

Sprite2D::~Sprite2D()
{	
}
