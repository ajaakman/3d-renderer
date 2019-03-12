#include "Renderable.h"

#include "../GUtility/TextureCache.h"

Renderable::Renderable(const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color), p_mTexture(nullptr), p_mSpecularTexture(nullptr), p_mMaterial(nullptr)
{	
	p_mTexture = TextureCache::UseTexture(path);
	p_mSpecularTexture = TextureCache::UseTexture(specularPath);
	p_mMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 5.f, p_mTexture, p_mSpecularTexture, this);
}

Renderable::Renderable(const glm::vec3 & position, const glm::vec3 & scale, const glm::vec3 & rotation, const glm::vec4 & color)
	: Position(position), Scale(scale), Rotation(rotation), Color(color)
{
}

Renderable::~Renderable()
{
	delete p_mMaterial;
	delete p_mSpecularTexture;
}
