#pragma once

#include "../../Libraries/glm/glm.hpp"
#include "../GLBase/Program.h"
#include "../GLBase/Texture.h"

class Material
{
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specularStrength, Texture* diffuseTexture, Texture* specularTexture);

	void Use(Program* program);

private:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float SpecularStrength;
	Texture* DiffuseTexture;
	Texture* SpecularTexture;
};