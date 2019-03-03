#include "SimpleRenderable.h"

#include "Vertex.h"

#include "../Libraries/glm/gtc/matrix_transform.hpp"

SimpleRenderable::SimpleRenderable(glm::vec2 position, glm::vec2 scale, int centered)
	: Position(position), Scale(scale), Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	float rootX = 0.0f, rootY = 0.0f;
	if (centered)
	{
		rootX = -0.5f; 
		rootY = -0.5f;
	}
	float vertices[8] = {
					  rootX,        rootY,
			   1.0f + rootX,        rootY,
		 	   1.0f + rootX, 1.0f + rootY,
					  rootX, 1.0f + rootY
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	Vertex vertex;
	vertex.PushFloat(2);

	p_Buffer = new Buffer(vertices, 4 * 2 * sizeof(float), vertex, GL_STATIC_DRAW);
	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 6, GL_STATIC_DRAW);
	p_Program = new Program();
}

SimpleRenderable::~SimpleRenderable()
{
	delete p_ElementArrayBuffer;
	delete p_Program;
	delete p_Buffer;
}

void SimpleRenderable::Draw(const glm::mat4 & view_projection)
{
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();		
	p_Program->Bind();

	glm::mat4 LocationMat = glm::translate(view_projection, glm::vec3(Position.x, Position.y, 0.0f));
	glm::mat4 RotationMat = glm::rotate(LocationMat, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));	
	glm::mat4 ScaleMat = glm::scale(RotationMat, glm::vec3(Scale.x, Scale.y, 1.0f));
		
	p_Program->SetUniformMat4f("u_MVP", ScaleMat);
	p_Program->SetUniform4f("u_Color", Color);
	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}


void SimpleRenderable::ModifyBuffer(glm::vec2 position, glm::vec2 size, int centered) // Can use to change root point.
{
	float rootX = 0.0f, rootY = 0.0f;
	if (centered)
	{
		rootX = -0.5f;
		rootY = -0.5f;
	}
	float vertices[8] = {
					  rootX,        rootY,
			   1.0f + rootX,        rootY,
			   1.0f + rootX, 1.0f + rootY,
					  rootX, 1.0f + rootY
	};
	p_Buffer->ModifyBuffer(vertices, 0, 4 * 2 * sizeof(float));
}
