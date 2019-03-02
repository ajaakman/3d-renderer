#include "SimpleRenderable.h"

#include "../Libraries/glm/gtc/matrix_transform.hpp"

SimpleRenderable::SimpleRenderable(glm::vec2 position, glm::vec2 size, int centered)
	: m_Position(position), m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), m_Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	float rootX = 0, rootY = 0;
	if (centered)
	{
		rootX -= size.x / 2;
		rootY -= size.y / 2;
	}
	float positions[8] = {
					 rootX,          rootY,
			size.x + rootX,          rootY,
			size.x + rootX, size.y + rootY,
					 rootX, size.y + rootY
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	p_VertexArray = new VertexArray;
	p_Buffer = new Buffer(positions, 4 * 2 * sizeof(float), GL_DYNAMIC_DRAW);

	Vertex vertex;
	vertex.PushFloat(2);
	p_VertexArray->AddBuffer(*p_Buffer, vertex);

	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 6, GL_DYNAMIC_DRAW);

	p_Program = new Program();
}

SimpleRenderable::~SimpleRenderable()
{
	delete p_ElementArrayBuffer;
	delete p_VertexArray;
	delete p_Program;
	delete p_Buffer;
}

void SimpleRenderable::Draw(const glm::mat4 & view_projection)
{
	p_Program->Bind();
	p_VertexArray->Bind();
	p_ElementArrayBuffer->Bind();		

	glm::mat4 MVP = 
	glm::rotate
	(
		glm::translate
		(
			view_projection, 
			glm::vec3(m_Position.x, m_Position.y, 0.0f) // Model Location
		),
		m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f) // Model Rotation
	);
		
	p_Program->SetUniformMat4f("u_MVP", MVP);
	p_Program->SetUniform4f("u_Color", m_Color);
	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void SimpleRenderable::SetColor(glm::vec4 color)
{
	m_Color = color;
}

void SimpleRenderable::SetPosition(glm::vec2 position)
{
	m_Position = position;
}

void SimpleRenderable::SetRotation(glm::vec3 rotation)
{
	m_Rotation = rotation;
}

