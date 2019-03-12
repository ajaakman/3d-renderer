#pragma once
#include <unordered_map>
#include <string>

#include "GLBase/Buffer.h"
#include "GLBase/ElementArrayBuffer.h"
#include "GLBase/Program.h"
#include "GLBase/Texture.h"
#include "Renderables/Renderable.h"
#include "../IO/Window.h"

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Clear();
	void Draw();

	bool Create(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path = "none", const std::string & specularPath = "", const glm::vec3 & rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec4 & color = glm::vec4(1.f, 1.f, 1.f, 1.f));
	bool CreateS(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path = "none", const std::string & specularPath = "", const glm::vec3 & rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec4 & color = glm::vec4(1.f, 1.f, 1.f, 1.f));
	Renderable* Find(const std::string & name);
	Renderable* FindS(const std::string & name);
		
	glm::vec3 CameraPosition;
	glm::vec3 CameraRotation;

	glm::vec3 LightPos;
private:
	glm::vec3 WorldUp;

	Window* m_pWindow;

	std::unordered_map<std::string, Renderable*> m_Renderables;
	std::unordered_map<std::string, Renderable*> m_Sprites;

	ElementArrayBuffer* p_ElementArrayBuffer;
	Program* p_Program;
	Buffer* p_Buffer;

	ElementArrayBuffer* p_SpriteElementArrayBuffer;
	Program* p_SpriteProgram;
	Buffer* p_SpriteBuffer;
};

