#pragma once

#include "../../Libraries/glm/glm.hpp"
#include "../GLBase/Program.h"
#include "../GLBase/Texture.h"

class Renderable;

class Material
{
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specularStrength, Texture* diffuseTexture, Texture* specularTexture, Renderable* parent);

	void Use(Program* program, const glm::mat4 & projectionView, const glm::vec3 & camera, const glm::vec3 & light);

private:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float SpecularStrength;
	Texture* p_DiffuseTexture;
	Texture* p_SpecularTexture;
	Renderable * p_ParentRenderable;
};