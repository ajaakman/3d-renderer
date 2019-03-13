#pragma once
#include <unordered_map>
#include <string>

#include "GLBase/Buffer.h"
#include "GLBase/ElementArrayBuffer.h"
#include "GLBase/Program.h"
#include "GLBase/Texture.h"
#include "Cameras/Camera.h"
#include "Renderables/Renderable.h"
#include "../IO/Window.h"

class SimpleRenderer
{
public:
	SimpleRenderer(Window* window);
	~SimpleRenderer();

	void Clear();
	void Draw();

	Renderable*& CreateCube(const glm::vec3 & position, const glm::vec3 & scale, const std::string & path = "none", const std::string & specularPath = "", const glm::vec3 & rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec4 & color = glm::vec4(1.f, 1.f, 1.f, 1.f));
	Renderable*& CreateSprite(const glm::vec3 & position, const glm::vec3 & scale, const std::string & path = "none", const std::string & specularPath = "", const glm::vec3 & rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec4 & color = glm::vec4(1.f, 1.f, 1.f, 1.f));
			
	inline Camera* GetCamera3D() const { return m_pCamera3D; }
	inline Camera* GetCamera2D() const { return m_pCamera2D; }
	
	glm::vec3 LightPos;
private:

	Window* m_pWindow;
	Camera* m_pCamera3D;
	Camera* m_pCamera2D;

	std::vector<Renderable*> m_Renderables;
	std::vector<Renderable*> m_Sprites;

	ElementArrayBuffer* p_ElementArrayBuffer;
	Program* p_Program;
	Buffer* p_Buffer;

	ElementArrayBuffer* p_SpriteElementArrayBuffer;
	Program* p_SpriteProgram;
	Buffer* p_SpriteBuffer;
};

