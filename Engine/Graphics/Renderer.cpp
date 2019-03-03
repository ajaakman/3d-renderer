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
	:m_pWindow(window)
{	
	GL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	GL(glEnable(GL_DEPTH_TEST));
	GL(glEnable(GL_CULL_FACE));

	GL(glEnable(GL_BLEND));
	GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GL(glCullFace(GL_BACK));
	GL(glFrontFace(GL_CCW));
#ifndef EMSCRIPTEN
	GL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)); // GL_FILL
#endif
}

Renderer::~Renderer()
{
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
		(
			0.0f, (float)m_pWindow->GetWidth(), 0.0f, (float)m_pWindow->GetHeight(), -1.0f, 1.0f // Projection
		),
		glm::vec3(0.0f, 0.0f, 0.0f) // View
	);

	for (auto & simpleRenderable : m_SimpleRenderables)
		simpleRenderable.second->Draw(ViewProjection);

	ViewProjection =
		glm::translate
		(
			//glm::ortho ( 0.0f, (float)m_pWindow->GetWidth(), 0.0f, (float)m_pWindow->GetHeight(), 1.0f, 500.0f),
			glm::perspective(75.0f, (float)m_pWindow->GetWidth()/(float)m_pWindow->GetHeight(), 1.0f, 10000.0f),
			glm::vec3(0.0f, 0.0f, -200.0f)
		);

	for (auto & Renderable3d : m_Renderables3d)
		Renderable3d.second->Draw(ViewProjection);
}

bool Renderer::CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered)
{
	if (!(m_SimpleRenderables.emplace(name, new SimpleRenderable(position, size, centered)).second))
	{
		std::cout << "Failed to create SimpleRenderable. Renderable with this name " << name << " already exists.\n";
		return false;
	}
	return true;
}

bool Renderer::CreateRenderable3d(const std::string & name, const glm::vec3 & position, const glm::vec3 & size)
{
	if (!(m_Renderables3d.emplace(name, new Renderable3d(position, size)).second))
	{
		std::cout << "Failed to create Renderable3d. Renderable with this name " << name << " already exists.\n";
		return false;
	}
	return true;
}

SimpleRenderable* Renderer::GetSimpleRenderable(const std::string & name)
{
	auto result = m_SimpleRenderables.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_SimpleRenderables.end() ? nullptr : m_SimpleRenderables.find(name)->second;
}

Renderable3d * Renderer::GetRenderable3d(const std::string & name)
{
	auto result = m_Renderables3d.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_Renderables3d.end() ? nullptr : m_Renderables3d.find(name)->second;
}
