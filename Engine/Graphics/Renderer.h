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

	bool CreateSprite2D(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const glm::vec3 & rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec4 & color = glm::vec4(1.f, 1.f, 1.f, 1.f));
	bool CreateRenderable3D(const std::string & name, const glm::vec3 & position, const glm::vec3 & scale);

	Renderable* GetSprite2D(const std::string & name);
	Renderable* GetRenderable3D(const std::string & name);
		
	glm::vec3 CameraPosition;
	glm::vec3 CameraRotation;

	glm::vec3 LightPos;
private:
	glm::vec3 WorldUp;

	Window* m_pWindow;

	std::unordered_map<std::string, Renderable*> m_Sprites2D;
	std::unordered_map<std::string, Renderable*> m_Renderables3D;

	ElementArrayBuffer* p_SpriteElementArrayBuffer;
	Program* p_SpriteProgram;
	Buffer* p_SpriteBuffer;

	ElementArrayBuffer* p_3DElementArrayBuffer;
	Program* p_3DProgram;
	Buffer* p_3DBuffer;

};

