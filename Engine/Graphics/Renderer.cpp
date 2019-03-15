#include "Renderer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>

#include "../Utility/Error.h"
#include "Cameras/Camera3D.h"
#include "Cameras/Camera2D.h"
#include "Meshes/Primitives.h"

SimpleRenderer::SimpleRenderer(Window* window)
	:m_pWindow(window), m_Cube(Mesh::CUBE), m_Sprite(Mesh::SPRITE)
{	
	m_pCamera3D = new Camera3D(m_pWindow, 0.5f, 1.f);
	m_pCamera2D = new Camera2D(m_pWindow, 0.2f);

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
}

SimpleRenderer::~SimpleRenderer()
{	
	delete m_pCamera3D;
	delete m_pCamera2D;
}

void SimpleRenderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void SimpleRenderer::Draw()
{			
	m_Cube.Draw(m_Renderables, m_pCamera3D);		
	m_Sprite.Draw(m_Sprites, m_pCamera2D);
}

Renderable*& SimpleRenderer::CreateCube(const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
{
	m_Renderables.push_back(new Renderable(position, scale, path, specularPath, rotation, color));
	return m_Renderables.back();
}

Renderable*& SimpleRenderer::CreateSprite(const glm::vec3 & position, const glm::vec3 & scale, const std::string & path, const std::string & specularPath, const glm::vec3 & rotation, const glm::vec4 & color)
{
	m_Sprites.push_back(new Renderable(position, scale, path, specularPath, rotation, color));
	return m_Sprites.back();
}

