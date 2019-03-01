#include "Renderer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>

#include "../Utility/Error.h"

Renderer::Renderer()
{	
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw()
{
	for (auto & simpleRenderable : m_SimpleRenderables)
		simpleRenderable.second->Draw();
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

SimpleRenderable* Renderer::GetSimpleRenderable(const std::string & name)
{
	auto result = m_SimpleRenderables.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_SimpleRenderables.end() ? nullptr : m_SimpleRenderables.find(name)->second;
}
