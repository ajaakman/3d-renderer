#include "SimpleRenderable.h"

#include "Vertex.h"

#include "../Libraries/glm/gtc/matrix_transform.hpp"

SimpleRenderable::SimpleRenderable(glm::vec2 position, glm::vec2 size, int centered)
	: Position(position), Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	float rootX = 0.0f, rootY = 0.0f;
	if (centered)
	{
		rootX -= size.x / 2.0f;
		rootY -= size.y / 2.0f;
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

	Vertex vertex;
	vertex.PushFloat(2);

	p_Buffer = new Buffer(positions, 4 * 2 * sizeof(float), vertex, GL_STATIC_DRAW);
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

	glm::mat4 LocationMat = glm::translate(view_projection, glm::vec3(Position.x, Position.y, 0.0f)); // Model Location
	glm::mat4 RotationMat = glm::rotate(LocationMat, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Model Rotation	
		
	p_Program->SetUniformMat4f("u_MVP", RotationMat);
	p_Program->SetUniform4f("u_Color", Color);
	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}


void SimpleRenderable::ModifyBuffer(glm::vec2 position, glm::vec2 size, int centered) // Can use to change root point.
{
	float rootX = position.x, rootY = position.y;
	if (centered)
	{
		rootX -= size.x / 2.0f;
		rootY -= size.y / 2.0f;
	}
	float positions[8] = {
					 rootX,          rootY,
			size.x + rootX,          rootY,
			size.x + rootX, size.y + rootY,
					 rootX, size.y + rootY
	};	
	p_Buffer->ModifyBuffer(positions, 0, 4 * 2 * sizeof(float));
}
