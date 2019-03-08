#include "Renderable.h"

#include "../GUtility/TextureCache.h"

Renderable::Renderable(glm::vec3 position, glm::vec3 scale, std::string path, glm::vec3 rotation, glm::vec4 color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color)
{	
	Texture = TextureCache::UseTexture(path);
}

Renderable::Renderable(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::vec4 color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color)
{
}

Renderable::~Renderable()
{	
}
