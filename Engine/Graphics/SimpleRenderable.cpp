#include "SimpleRenderable.h"

SimpleRenderable::SimpleRenderable(glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color)
{	
}

SimpleRenderable::~SimpleRenderable()
{	
}
