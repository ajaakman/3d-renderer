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
	:m_pWindow(window), CameraPosition(glm::vec3(0.f, 0.f, 0.f)), CameraRotation(glm::vec3(0.f, 0.f, -1.f)), WorldUp(glm::vec3(0.f, 1.f, 0.f)),	LightPos(glm::vec3(300.f, 300.f, -500.f))
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
	// 3D Models
	{
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

		p_Buffer = new Buffer(&vertices[0], vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
		p_ElementArrayBuffer = new ElementArrayBuffer(&indices[0], indices.size(), GL_STATIC_DRAW);
		p_Program = new Program("Resources/Shaders/Basic.shader");
	}
	// 2D Sprites
	{
		std::vector<float> vertices = {
							-0.5f, -0.5f,     1.f, 1.f,     0.f, 0.f, 1.f,
							 0.5f, -0.5f,     0.f, 1.f,     0.f, 0.f, 1.f,
							 0.5f,  0.5f,     0.f, 0.f,     0.f, 0.f, 1.f,
							-0.5f,  0.5f,     1.f, 0.f,     0.f, 0.f, 1.f,
		};

		std::vector<unsigned> indices = {
			0, 1, 2,
			0, 2, 3
		};

		std::vector<unsigned> layout = { 2, 2, 3 };
		VertexLayout vertex;
		for (auto & element : layout)
			vertex.PushFloat(element);

		p_SpriteBuffer = new Buffer(&vertices[0], vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
		p_SpriteElementArrayBuffer = new ElementArrayBuffer(&indices[0], indices.size(), GL_STATIC_DRAW);
		p_SpriteProgram = new Program("Resources/Shaders/Basic.shader");
	}
}

Renderer::~Renderer()
{
	delete p_ElementArrayBuffer;
	delete p_Program;
	delete p_Buffer;

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
	glm::mat4 PerspectiveProjectionView = glm::perspective(80.f, (float)m_pWindow->GetWidth() / (float)m_pWindow->GetHeight(), 1.f, 10000.f) 
								    	* (glm::lookAt(CameraPosition, CameraPosition + CameraRotation, WorldUp));
	glm::mat4 OrthoProjectionView = glm::translate ( glm::ortho ( 0.f, (float)m_pWindow->GetWidth(), 0.f, (float)m_pWindow->GetHeight(), -100.f, 100.f),	
													 glm::vec3(CameraPosition.x, CameraPosition.y, 0.f));	
	
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();
	p_Program->Bind();

	for (auto & renderable : m_Renderables)
	{
		renderable.second->GetMaterial()->Use(p_Program, PerspectiveProjectionView, CameraPosition, LightPos);
		GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}	

	p_SpriteBuffer->Bind();
	p_SpriteElementArrayBuffer->Bind();
	p_SpriteProgram->Bind();

	for (auto & sprite : m_Sprites)
	{
		sprite.second->GetMaterial()->Use(p_SpriteProgram, OrthoProjectionView, CameraPosition, LightPos);
		GL(glDrawElements(GL_TRIANGLES, p_SpriteElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}

bool Renderer::Create(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
{
	if (!(m_Renderables.emplace(name, new Renderable(position, scale, path, specularPath, rotation, color)).second))
	{
		std::cout << "Failed to create Renderable. Renderable with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

Renderable* Renderer::Find(const std::string & name)
{
	auto result = m_Renderables.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Renderables.end() ? nullptr : m_Renderables.find(name)->second;
}

bool Renderer::CreateS(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
{
	if (!(m_Sprites.emplace(name, new Renderable(position, scale, path, specularPath, rotation, color)).second))
	{
		std::cout << "Failed to create Sprite. Sprite with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

Renderable* Renderer::FindS(const std::string & name)
{
	auto result = m_Sprites.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Sprites.end() ? nullptr : m_Sprites.find(name)->second;
}
