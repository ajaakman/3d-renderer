#include "Renderer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>

#include "../Utility/Error.h"
#include "Cameras/Camera3D.h"
#include "Cameras/Camera2D.h"
#include "Meshes/Primitives.h"

SimpleRenderer::SimpleRenderer(Window* window)
	:m_pWindow(window),	LightPos(glm::vec3(300.f, 300.f, 500.f))
{	
	m_pCamera3D = new Camera3D(m_pWindow, 0.5f, 1.f);
	m_pCamera2D = new Camera2D(m_pWindow, 0.2f);

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
		Cube cube;
		VertexLayout vertex;
		for (auto & element : cube.layout)
			vertex.PushFloat(element);

		p_Buffer = new Buffer(&cube.vertices[0], cube.vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
		p_ElementArrayBuffer = new ElementArrayBuffer(&cube.indices[0], cube.indices.size(), GL_STATIC_DRAW);
		p_Program = new Program("Resources/Shaders/Basic.shader");
	}
	// 2D Sprites
	{		
		Sprite sprite;
		VertexLayout vertex;
		for (auto & element : sprite.layout)
			vertex.PushFloat(element);

		p_SpriteBuffer = new Buffer(&sprite.vertices[0], sprite.vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
		p_SpriteElementArrayBuffer = new ElementArrayBuffer(&sprite.indices[0], sprite.indices.size(), GL_STATIC_DRAW);
		p_SpriteProgram = new Program("Resources/Shaders/Basic.shader");
	}
}

SimpleRenderer::~SimpleRenderer()
{
	delete p_ElementArrayBuffer;
	delete p_Program;
	delete p_Buffer;

	delete p_SpriteElementArrayBuffer;
	delete p_SpriteProgram;
	delete p_SpriteBuffer;

	delete m_pCamera3D;
	delete m_pCamera2D;
}

void SimpleRenderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void SimpleRenderer::Draw()
{		
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();
	p_Program->Bind();

	for (auto & renderable : m_Renderables)
	{
		renderable.second->GetMaterial()->Use(p_Program, m_pCamera3D->GetMatrix(), m_pCamera3D->GetPosition(), LightPos);
		GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}	

	p_SpriteBuffer->Bind();
	p_SpriteElementArrayBuffer->Bind();
	p_SpriteProgram->Bind();

	for (auto & sprite : m_Sprites)
	{
		sprite.second->GetMaterial()->Use(p_SpriteProgram, m_pCamera2D->GetMatrix(), m_pCamera2D->GetPosition(), LightPos);
		GL(glDrawElements(GL_TRIANGLES, p_SpriteElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}

bool SimpleRenderer::Create(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
{
	if (!(m_Renderables.emplace(name, new Renderable(position, scale, path, specularPath, rotation, color)).second))
	{
		std::cout << "Failed to create Renderable. Renderable with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

Renderable* SimpleRenderer::Find(const std::string & name)
{
	auto result = m_Renderables.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Renderables.end() ? nullptr : m_Renderables.find(name)->second;
}

bool SimpleRenderer::CreateS(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
{
	if (!(m_Sprites.emplace(name, new Renderable(position, scale, path, specularPath, rotation, color)).second))
	{
		std::cout << "Failed to create Sprite. Sprite with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

Renderable* SimpleRenderer::FindS(const std::string & name)
{
	auto result = m_Sprites.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Sprites.end() ? nullptr : m_Sprites.find(name)->second;
}
