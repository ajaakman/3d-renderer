#pragma once
#include <unordered_map>
#include <string>

#include "SimpleRenderable.h"
#include "Renderable3d.h"
#include "../IO/Window.h"

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Clear();
	void Draw();
	bool CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered = 0);
	bool CreateRenderable3d(const std::string & name, const glm::vec3 & position, const glm::vec3 & size);
	SimpleRenderable* GetSimpleRenderable(const std::string & name);
	Renderable3d* GetRenderable3d(const std::string & name);
private:
	Window* m_pWindow;
	std::unordered_map<std::string, SimpleRenderable*> m_SimpleRenderables;
	std::unordered_map<std::string, Renderable3d*> m_Renderables3d;
};

