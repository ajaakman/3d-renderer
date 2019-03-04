#include "Sprite2D.h"

#include "Vertex.h"

#include "../Libraries/glm/gtc/matrix_transform.hpp"

Sprite2D::Sprite2D(glm::vec2 position, glm::vec2 scale, int centered)
	: Position(position), Scale(scale), Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), Rotation(0.0f)
{
	float rootX = 0.0f, rootY = 0.0f;
	if (centered)
	{
		rootX = -0.5f;
		rootY = -0.5f;
	}
	float vertices[16] = {
					  rootX,        rootY, 0.0f, 0.0f,
			   1.0f + rootX,        rootY, 1.0f, 0.0f,
			   1.0f + rootX, 1.0f + rootY, 1.0f, 1.0f,
					  rootX, 1.0f + rootY, 0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	Vertex vertex;
	vertex.PushFloat(2);
	vertex.PushFloat(2);

	p_Buffer = new Buffer(vertices, 4 * 4 * sizeof(float), vertex, GL_STATIC_DRAW);
	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 6, GL_STATIC_DRAW);
	p_Program = new Program(1);
}

Sprite2D::~Sprite2D()
{
	delete p_ElementArrayBuffer;
	delete p_Program;
	delete p_Buffer;
}

void Sprite2D::Draw(const glm::mat4 & view_projection)
{
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();
	p_Program->Bind();
	m_Texture.Bind(0);

	glm::mat4 LocationMat = glm::translate(view_projection, glm::vec3(Position.x, Position.y, 0.0f));
	glm::mat4 RotationMat = glm::rotate(LocationMat, Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMat = glm::scale(RotationMat, glm::vec3(Scale.x, Scale.y, 1.0f));

	p_Program->SetUniformMat4f("u_MVP", ScaleMat);
	p_Program->SetUniform1i("u_Texture", 0);
	p_Program->SetUniform4f("u_Color", Color);
	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));

	m_Texture.Unbind();
}


void Sprite2D::ModifyBuffer(glm::vec2 position, glm::vec2 size, int centered) // Can use to change root point.
{
	float rootX = 0.0f, rootY = 0.0f;
	if (centered)
	{
		rootX = -0.5f;
		rootY = -0.5f;
	}
	float vertices[16] = {
					  rootX,        rootY, 0.0f, 0.0f,
			   1.0f + rootX,        rootY, 1.0f, 0.0f,
			   1.0f + rootX, 1.0f + rootY, 1.0f, 1.0f,
					  rootX, 1.0f + rootY, 0.0f, 1.0f
	};
	p_Buffer->ModifyBuffer(vertices, 0, 4 * 2 * sizeof(float));
}
