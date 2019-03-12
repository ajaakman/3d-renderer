#include "Material.h"

#include "../Renderables/Renderable.h"

#include "../../Libraries/glm/gtc/matrix_transform.hpp"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specularFocus, Texture* diffuseTexture, Texture* specularTexture, Renderable* parent)
	:Ambient(ambient), Diffuse(diffuse), Specular(specular), SpecularFocus(specularFocus),
	 p_DiffuseTexture(diffuseTexture), p_SpecularTexture(specularTexture), p_ParentRenderable(parent)
{
}

void Material::Use(Program* program, const glm::mat4 & projectionView, const glm::vec3 & camera, const glm::vec3 & light)
{	
	glm::mat4 Location = glm::translate(glm::mat4(1.f), glm::vec3(p_ParentRenderable->Position.x, p_ParentRenderable->Position.y, p_ParentRenderable->Position.z));
	glm::mat4 RotationX = glm::rotate(Location, p_ParentRenderable->Rotation.x, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 RotationY = glm::rotate(RotationX, p_ParentRenderable->Rotation.y, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 RotationZ = glm::rotate(RotationY, p_ParentRenderable->Rotation.z, glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 Model = glm::scale(RotationZ, glm::vec3(p_ParentRenderable->Scale.x, p_ParentRenderable->Scale.y, p_ParentRenderable->Scale.z));
	
	program->SetUniformMat4f("u_MVP", projectionView * Model);
	program->SetUniformMat4f("u_Model", Model);
	program->SetUniform4f("u_Color", p_ParentRenderable->Color);
	program->SetUniform3f("u_Light", light);
	program->SetUniform3f("u_Camera", camera);

	program->SetUniform3f("material.ambient", Ambient);
	program->SetUniform3f("material.diffuse", Diffuse);
	program->SetUniform3f("material.specular", Specular);
	program->SetUniform1f("material.specularFocus", SpecularFocus);
	p_DiffuseTexture->Bind(0);
	program->SetUniform1i("material.diffuseTex", 0);
	p_SpecularTexture->Bind(1);
	program->SetUniform1i("material.specularTex", 1);
}