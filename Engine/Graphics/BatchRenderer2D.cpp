#include "BatchRenderer2D.h"

#include <iostream>

#include "../Libraries/glm/gtc/matrix_transform.hpp"

#include "Vertex.h"

#define RENDERABLES 2

BatchRenderer2D::BatchRenderer2D()
{
	float rootX = 0, rootY = 0;	

	rootX -= 50 / 2;
	rootY -= 50 / 2;
	
	float vertices[8 * RENDERABLES] = {
					 rootX,          rootY,
				50 + rootX,          rootY,
				50 + rootX,		50 + rootY,
					 rootX,		50 + rootY,
					 rootX+100,      rootY+100,
				50 + rootX+100,      rootY+100,
				50 + rootX+100, 50 + rootY+100,
					 rootX+100, 50 + rootY+100

	};

	unsigned int indices[6 * RENDERABLES] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4
	};

	Vertex vertex;
	vertex.PushFloat(2);

	p_Buffer = new Buffer(vertices, 4 * 2 * sizeof(float), vertex, GL_DYNAMIC_DRAW);
	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 6, GL_DYNAMIC_DRAW);
	p_Program = new Program();
}

BatchRenderer2D::~BatchRenderer2D()
{
	delete p_ElementArrayBuffer;
	delete p_Program;
	delete p_Buffer;
}

void BatchRenderer2D::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT));
}

void BatchRenderer2D::Draw()
{
	p_Program->Bind();
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();
	// TODO
	for (auto & renderable : m_SimpleRenderables)
	{
	glm::mat4 MVP =
		glm::rotate
		(
			glm::translate
			(
				glm::translate
				(
					glm::ortho
					(
						0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f // Projection
					),
					glm::vec3(0.0f, 0.0f, 0.0f) // View
				),
				glm::vec3(renderable.second->m_Position.x, renderable.second->m_Position.y, 0.0f) // Model Location
			),
			renderable.second->m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f) // Model Rotation
		);

	p_Program->SetUniformMat4f("u_MVP", MVP);
	p_Program->SetUniform4f("u_Color", renderable.second->m_Color);
	}

	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

bool BatchRenderer2D::CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered)
{
	if (!(m_SimpleRenderables.emplace(name, new SimpleBatchRenderable(position, size, centered)).second))
	{
		std::cout << "Failed to create SimpleRenderable. Renderable with this name " << name << " already exists.\n";
		return false;
	}
	return true;
}

BatchRenderer2D::SimpleBatchRenderable * BatchRenderer2D::GetSimpleRenderable(const std::string & name)
{
	auto result = m_SimpleRenderables.find(name);
	// TODO Fatal error if wrong name is used.
	return result == m_SimpleRenderables.end() ? nullptr : m_SimpleRenderables.find(name)->second;
}

BatchRenderer2D::SimpleBatchRenderable::SimpleBatchRenderable(glm::vec2 position, glm::vec2 size, int centered)
	:m_Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), m_Position(position), m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

BatchRenderer2D::SimpleBatchRenderable::~SimpleBatchRenderable()
{
}

void BatchRenderer2D::SimpleBatchRenderable::SetColor(glm::vec4 color)
{
	m_Color = color;
}

void BatchRenderer2D::SimpleBatchRenderable::SetPosition(glm::vec2 position)
{
	m_Position = position;
}

void BatchRenderer2D::SimpleBatchRenderable::SetRotation(glm::vec3 rotation)
{
	m_Rotation = rotation;
}
