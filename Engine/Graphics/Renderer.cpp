#include "Renderer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>

#include "../Libraries/glm/gtc/matrix_transform.hpp"

#include "../Utility/Error.h"

Renderer::Renderer(Window* window)
	:m_pWindow(window), CameraPosition(glm::vec3(0.f, 0.f, 0.f)), CameraRotation(glm::vec3(0.f, 0.f, -1.f)), WorldUp(glm::vec3(0.f, 1.f, 0.f)),	LightPos(glm::vec3(540.f, -540.f, 10.f))
{	
	GL(glClearColor(0.1f, 0.1f, 0.1f, 1.f));
	//GL(glEnable(GL_DEPTH_TEST));
	GL(glEnable(GL_CULL_FACE));

	GL(glEnable(GL_BLEND));
	GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GL(glCullFace(GL_BACK));
	GL(glFrontFace(GL_CCW));
#ifndef EMSCRIPTEN
	GL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)); // GL_FILL GL_LINE
#endif		
		
	std::vector<float> vertices = {
						-0.5f, -0.5f,  0.5f,     1.f, 1.f,    -0.5f, -0.5f,  0.5f,
					 	 0.5f, -0.5f,  0.5f,     0.f, 1.f,     0.5f, -0.5f,  0.5f,
					  	 0.5f,  0.5f,  0.5f,     0.f, 0.f,     0.5f,  0.5f,  0.5f,
						-0.5f,  0.5f,  0.5f,     1.f, 0.f,    -0.5f,  0.5f,  0.5f,
						-0.5f, -0.5f, -0.5f,     0.f, 1.f,    -0.5f, -0.5f, -0.5f,
						 0.5f, -0.5f, -0.5f,     1.f, 1.f,     0.5f, -0.5f, -0.5f,
						 0.5f,  0.5f, -0.5f,     1.f, 0.f,     0.5f,  0.5f, -0.5f,
						-0.5f,  0.5f, -0.5f,     0.f, 0.f,    -0.5f,  0.5f, -0.5f
	};
		

	std::vector<unsigned> indices = {
		0, 1, 2,
		0, 2, 3,
		1, 6, 2,
		1, 5, 6,
		4, 7, 5,
		7, 6, 5,
		3, 7, 4,
		0, 3, 4,
		3, 6, 7,
		3, 2, 6,
		0, 4, 5,
		0, 5, 1
	};

	std::vector<unsigned> layout = { 3, 2, 3 };
	VertexLayout vertex;
	for (auto & element : layout)
		vertex.PushFloat(element);

	p_SpriteBuffer = new Buffer(&vertices[0], vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
	p_SpriteElementArrayBuffer = new ElementArrayBuffer(&indices[0], indices.size(), GL_STATIC_DRAW);
	p_SpriteProgram = new Program("Resources/Shaders/Basic.shader");
	
}

Renderer::~Renderer()
{
	delete p_SpriteElementArrayBuffer;
	delete p_SpriteProgram;
	delete p_SpriteBuffer;
}

void Renderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void Renderer::Draw()
{
	glm::mat4 Projection = glm::perspective(80.f, (float)m_pWindow->GetWidth() / (float)m_pWindow->GetHeight(), 1.f, 10000.f);
	glm::mat4 View = (glm::lookAt(CameraPosition, CameraPosition + CameraRotation, WorldUp));
		
	//glm::mat4 OrthoProjectionView = glm::translate (	glm::ortho ( 0.f, (float)m_pWindow->GetWidth(), 0.f, (float)m_pWindow->GetHeight(), -100.f, 100.f),	
	//	glm::vec3(CameraPosition.x, CameraPosition.y, 0.f));	
	
	p_SpriteBuffer->Bind();
	p_SpriteElementArrayBuffer->Bind();
	p_SpriteProgram->Bind();

	for (auto & renderable : m_Sprites2D)
	{
		glm::mat4 Location = glm::translate(glm::mat4(1.f), glm::vec3(renderable.second->Position.x, renderable.second->Position.y, renderable.second->Position.z));
		glm::mat4 RotationX = glm::rotate(Location, renderable.second->Rotation.x, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 RotationY = glm::rotate(RotationX, renderable.second->Rotation.y, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 RotationZ = glm::rotate(RotationY, renderable.second->Rotation.z, glm::vec3(0.f, 0.f, 1.f));
		glm::mat4 Model = glm::scale(RotationZ, glm::vec3(renderable.second->Scale.x, renderable.second->Scale.y, renderable.second->Scale.z));

		renderable.second->GetMaterial()->Use(p_SpriteProgram);

		p_SpriteProgram->SetUniformMat4f("u_MVP", Projection * View * Model);
		p_SpriteProgram->SetUniformMat4f("u_Model", Model);
		p_SpriteProgram->SetUniform4f("u_Color", renderable.second->Color);
		p_SpriteProgram->SetUniform3f("u_Light", LightPos);
		p_SpriteProgram->SetUniform3f("u_Camera", CameraPosition);
		GL(glDrawElements(GL_TRIANGLES, p_SpriteElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
	
}

bool Renderer::Create(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const glm::vec3 & rotation, const glm::vec4 & color)
{
	if (!(m_Sprites2D.emplace(name, new Renderable(position, scale, path, rotation, color)).second))
	{
		std::cout << "Failed to create Sprite2D. Sprite with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

Renderable* Renderer::Find(const std::string & name)
{
	auto result = m_Sprites2D.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Sprites2D.end() ? nullptr : m_Sprites2D.find(name)->second;
}
