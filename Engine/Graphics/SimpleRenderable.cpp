#include "SimpleRenderable.h"
#include "../Libraries/glm/gtc/matrix_transform.hpp"

SimpleRenderable::SimpleRenderable(glm::vec2 position, glm::vec2 size, int centered)
	: m_Position(position), m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), m_Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	float originX = 0;
	float originY = 0;
	if (centered)
	{
		originX -= size.x / 2;
		originY -= size.y / 2;
	}

	float positions[8] = {
					 originX,          originY,
			size.x + originX,          originY,
			size.x + originX, size.y + originY,
					 originX, size.y + originY
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	p_VertexArray = new VertexArray;
	p_Buffer = new Buffer(positions, 4 * 2 * sizeof(float));
	//Buffer buffer(positions, 4 * 2 * sizeof(float));

	Vertex vertex;
	vertex.PushFloat(2);
	p_VertexArray->AddBuffer(*p_Buffer, vertex);
	//p_VertexArray->AddBuffer(buffer, vertex);

	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 6);
#ifdef EMSCRIPTEN
	p_Program = new Program("Resources/EmShaders/Basic.shader");
#else
	p_Program = new Program("../Resources/Shaders/Basic.shader");
#endif
	p_Program->Bind();
	p_Program->SetUniform4f("u_Color", m_Color);
	p_Program->SetUniformMat4f("u_MVP", glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f));
}

void SimpleRenderable::Draw()
{
	p_Program->Bind();
	p_VertexArray->Bind();
	p_ElementArrayBuffer->Bind();

	glm::mat4 Projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 Translation = glm::translate(glm::mat4(), glm::vec3(m_Position.x, m_Position.y, 0.0f));
	glm::mat4 Rotation = glm::rotate(glm::mat4(), m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 Model = Translation * Rotation;

	glm::mat4 MVP = Projection * View * Model;

	p_Program->SetUniform4f("u_Color", m_Color);
	p_Program->SetUniformMat4f("u_MVP", MVP);

	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

SimpleRenderable::~SimpleRenderable()
{
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
