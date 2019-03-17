#pragma once
#include <unordered_map>
#include <string>

#include "Cameras/Camera.h"
#include "Renderables/Renderable.h"
#include "../IO/Window.h"
#include "Meshes/Mesh.h"

class SimpleRenderer
{
public:
	SimpleRenderer(Window* window);
	~SimpleRenderer();

	void Clear();
	void Draw();

	Renderable*& Render(Mesh::Primitive type, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path = "none", const std::string & specularPath = "", const glm::vec3 & rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec4 & color = glm::vec4(1.f, 1.f, 1.f, 1.f));
			
	inline Camera* GetCamera3D() const& { return m_pCamera3D; }
	inline Camera* GetCamera2D() const& { return m_pCamera2D; }
	
private:
	glm::vec3 LightPos;

	Mesh m_CubeMesh;
	Mesh m_ModelMesh;
	Mesh m_SpriteMesh;

	Window* m_pWindow;
	Camera* m_pCamera3D;
	Camera* m_pCamera2D;

	std::vector<Renderable*> m_Renderables;
	std::vector<Renderable*> m_Models;
	std::vector<Renderable*> m_Sprites;	
};

