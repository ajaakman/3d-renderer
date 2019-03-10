#pragma once

#include "../Libraries/glm/glm.hpp"
#include "GLBase/Program.h"

class Material
{
public:
	Material(glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	float specularStrength,
	Texture* diffuseTex,
	Texture* specularTex)
	{
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
		SpecularStrength = specularStrength;
		DiffuseTex = diffuseTex;
		SpecularTex = specularTex;
	}

	void Use(Program* program)
	{
		DiffuseTex->Bind();
		//SpecularTex->Bind();
		program->SetUniform3f("material.ambient", Ambient);
		program->SetUniform3f("material.diffuse", Diffuse);
		program->SetUniform3f("material.specular", Specular);
		program->SetUniform1f("material.specularStrength", SpecularStrength);
		program->SetUniform1i("material.diffuseTex", 0);
		program->SetUniform1i("material.specularTex", 1);
	}

private:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float SpecularStrength;
	Texture* DiffuseTex;
	Texture* SpecularTex;
};