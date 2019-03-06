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
	:m_pWindow(window), CameraPosition(glm::vec3(0.f, 0.f, -200.f)), CameraRotation(glm::vec3(0.f, 0.f, -1.f)), WorldUp(glm::vec3(0.f, 1.f, 0.f))
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
	{
		float vertices[8] = {
						  -0.5f, -0.5f,
						   0.5f, -0.5f,
						   0.5f,  0.5f,
						  -0.5f,  0.5f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		Vertex vertex;
		vertex.PushFloat(2);

		p_SimpleBuffer = new Buffer(vertices, 4 * 2 * sizeof(float), vertex, GL_STATIC_DRAW);
		p_SimpleElementArrayBuffer = new ElementArrayBuffer(indices, 6, GL_STATIC_DRAW);
		p_SimpleProgram = new Program();
	}
	{
		float vertices[] = {
						  -1.000000, -1.000000,  1.000000,
						  -1.000000, -1.000000, -1.000000,
						   1.000000, -1.000000, -1.000000,
						   1.000000, -1.000000,  1.000000,
						  -1.000000,  1.000000,  1.000000,
						  -1.000000,  1.000000, -1.000000,
						   1.000000,  1.000000, -1.000000,
						   1.000000,  1.000000,  1.000000
		};

		unsigned int indices[] = {
			1, 3, 0,
			7, 5, 4,
			4, 1, 0,
			5, 2, 1,
			2, 7, 3,
			0, 7, 4,
			1, 2, 3,
			7, 6, 5,
			4, 5, 1,
			5, 6, 2,
			2, 6, 7,
			0, 3, 7
		};

		Vertex vertex;
		vertex.PushFloat(3);

		p_3DBuffer = new Buffer(vertices, 8 * 3 * sizeof(float), vertex, GL_STATIC_DRAW);
		p_3DElementArrayBuffer = new ElementArrayBuffer(indices, 36, GL_STATIC_DRAW);
		p_3DProgram = new Program(0);
	}
	{		
		float vertices[] = {
						  -0.5f, -0.5f, 0.f, 0.f,
						   0.5f, -0.5f, 1.f, 0.f,
						   0.5f,  0.5f, 1.f, 1.f,
						  -0.5f,  0.5f, 0.f, 1.f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		Vertex vertex;
		vertex.PushFloat(2);
		vertex.PushFloat(2);

		p_SpriteBuffer = new Buffer(vertices, 4 * 4 * sizeof(float), vertex, GL_STATIC_DRAW);
		p_SpriteElementArrayBuffer = new ElementArrayBuffer(indices, 6, GL_STATIC_DRAW);
		p_SpriteProgram = new Program(1);
	}
}

Renderer::~Renderer()
{
	delete p_SimpleElementArrayBuffer;
	delete p_SimpleProgram;
	delete p_SimpleBuffer;

	delete p_SpriteElementArrayBuffer;
	delete p_SpriteProgram;
	delete p_SpriteBuffer;

	delete p_3DElementArrayBuffer;
	delete p_3DProgram;
	delete p_3DBuffer;
}

void Renderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void Renderer::Draw()
{
	glm::mat4 ViewProjection =
	glm::translate
	(
		glm::ortho
		( 0.f, (float)m_pWindow->GetWidth(), 0.f, (float)m_pWindow->GetHeight(), -1.f, 1.f),
		glm::vec3(CameraPosition.x/20, CameraPosition.y/20, 0.f) // View
	);

	p_SpriteBuffer->Bind();
	p_SpriteElementArrayBuffer->Bind();
	p_SpriteProgram->Bind();

	for (auto & sprite : m_Sprites2D)
	{
		sprite.second->Texture->Bind(0);
		glm::mat4 LocationMat = glm::translate(ViewProjection, glm::vec3(sprite.second->Position.x, sprite.second->Position.y, 0.f));
		glm::mat4 RotationMat = glm::rotate(LocationMat, sprite.second->Rotation, glm::vec3(0.f, 0.f, 1.f));
		glm::mat4 ScaleMat = glm::scale(RotationMat, glm::vec3(sprite.second->Scale.x, sprite.second->Scale.y, 1.f));

		p_SpriteProgram->SetUniformMat4f("u_MVP", ScaleMat);
		p_SpriteProgram->SetUniform1i("u_Texture0", 0);
		p_SpriteProgram->SetUniform4f("u_Color", sprite.second->Color);
		GL(glDrawElements(GL_TRIANGLES, p_SpriteElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	p_SimpleBuffer->Bind();
	p_SimpleElementArrayBuffer->Bind();
	p_SimpleProgram->Bind();

	for (auto & renderable : m_SimpleRenderables)
	{
		glm::mat4 LocationMat = glm::translate(ViewProjection, glm::vec3(renderable.second->Position.x, renderable.second->Position.y, 0.f));
		glm::mat4 RotationMat = glm::rotate(LocationMat, renderable.second->Rotation, glm::vec3(0.f, 0.f, 1.f));
		glm::mat4 ScaleMat = glm::scale(RotationMat, glm::vec3(renderable.second->Scale.x, renderable.second->Scale.y, 1.f));

		p_SimpleProgram->SetUniformMat4f("u_MVP", ScaleMat);
		p_SimpleProgram->SetUniform4f("u_Color", renderable.second->Color);
		GL(glDrawElements(GL_TRIANGLES, p_SimpleElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	glm::mat4 Projection = glm::perspective(75.f, (float)m_pWindow->GetWidth() / (float)m_pWindow->GetHeight(), 1.f, 10000.f);
	glm::mat4 View = (glm::lookAt(CameraPosition, CameraPosition + CameraRotation, WorldUp));

	p_3DBuffer->Bind();
	p_3DElementArrayBuffer->Bind();
	p_3DProgram->Bind();

	for (auto & renderable : m_Renderables3D)
	{
		glm::mat4 LocationMat = glm::translate(Projection * View, glm::vec3(renderable.second->Position.x, renderable.second->Position.y, renderable.second->Position.z));
		glm::mat4 RotationMatx = glm::rotate(LocationMat, renderable.second->Rotation.x, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 RotationMaty = glm::rotate(RotationMatx, renderable.second->Rotation.y, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 RotationMatz = glm::rotate(RotationMaty, renderable.second->Rotation.z, glm::vec3(0.f, 0.f, 1.f));
		glm::mat4 ScaleMat = glm::scale(RotationMatz, glm::vec3(renderable.second->Scale.x, renderable.second->Scale.y, renderable.second->Scale.z));

		p_3DProgram->SetUniformMat4f("u_MVP", ScaleMat);
		p_3DProgram->SetUniform1i("u_Texture0", 0);
		p_3DProgram->SetUniform4f("u_Color", renderable.second->Color);
		GL(glDrawElements(GL_TRIANGLES, p_3DElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

}

bool Renderer::CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & scale, const float & rotation, const glm::vec4 & color)
{
	if (!(m_SimpleRenderables.emplace(name, new Sprite2D(position, scale, rotation, color)).second))
	{
		std::cout << "Failed to create SimpleRenderable. Renderable with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

bool Renderer::CreateSprite2D(const std::string & name, const glm::vec2 & position, const glm::vec2 & scale, const std::string & path, const float & rotation, const glm::vec4 & color)
{
	if (!(m_Sprites2D.emplace(name, new Sprite2D(position, scale, path, rotation, color)).second))
	{
		std::cout << "Failed to create Sprite2D. Sprite with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

bool Renderer::CreateRenderable3D(const std::string & name, const glm::vec3 & position, const glm::vec3 & size)
{
	if (!(m_Renderables3D.emplace(name, new Renderable3D(position, size)).second))
	{
		std::cout << "Failed to create Renderable3d. Renderable with name " << name << " already exists.\n";
		return false;
	}
	return true;
}

Sprite2D* Renderer::GetSimpleRenderable(const std::string & name)
{
	auto result = m_SimpleRenderables.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_SimpleRenderables.end() ? nullptr : m_SimpleRenderables.find(name)->second;
}

Sprite2D * Renderer::GetSprite2D(const std::string & name)
{
	auto result = m_Sprites2D.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Sprites2D.end() ? nullptr : m_Sprites2D.find(name)->second;
}

Renderable3D * Renderer::GetRenderable3D(const std::string & name)
{
	auto result = m_Renderables3D.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Renderables3D.end() ? nullptr : m_Renderables3D.find(name)->second;
}
