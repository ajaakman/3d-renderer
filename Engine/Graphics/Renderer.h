#pragma once
#include <unordered_map>
#include <string>

#include "SimpleRenderable.h"
#include "Renderable3D.h"
#include "Sprite2D.h"
#include "../IO/Window.h"

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Clear();
	void Draw();
	bool CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered = 0);
	bool CreateSprite2D(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered = 0);
	bool CreateRenderable3D(const std::string & name, const glm::vec3 & position, const glm::vec3 & size);
	SimpleRenderable* GetSimpleRenderable(const std::string & name);
	Sprite2D* GetSprite2D(const std::string & name);
	Renderable3D* GetRenderable3D(const std::string & name);
private:
	Window* m_pWindow;
	std::unordered_map<std::string, SimpleRenderable*> m_SimpleRenderables;
	std::unordered_map<std::string, Sprite2D*> m_Sprites2D;
	std::unordered_map<std::string, Renderable3D*> m_Renderables3D;
};

