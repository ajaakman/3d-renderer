#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specularStrength, Texture* diffuseTexture, Texture* specularTexture)
	:Ambient(ambient), Diffuse(diffuse), Specular(specular), SpecularStrength(specularStrength), DiffuseTexture(diffuseTexture), SpecularTexture(specularTexture)
{
}

void Material::Use(Program* program)
{
	DiffuseTexture->Bind();
	//SpecularTexture->Bind();
	program->SetUniform3f("material.ambient", Ambient);
	program->SetUniform3f("material.diffuse", Diffuse);
	program->SetUniform3f("material.specular", Specular);
	program->SetUniform1f("material.specularStrength", SpecularStrength);
	program->SetUniform1i("material.diffuseTex", 0);
	program->SetUniform1i("material.specularTex", 1);
}