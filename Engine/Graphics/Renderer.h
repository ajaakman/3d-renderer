#pragma once
#include <unordered_map>
#include <string>

#include "SimpleRenderable.h"
#include "../IO/Window.h"

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Clear();
	void Draw();
	bool CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered = 0);
	SimpleRenderable* GetSimpleRenderable(const std::string & name);
private:
	Window* m_pWindow;
	std::unordered_map<std::string, SimpleRenderable*> m_SimpleRenderables;
};

