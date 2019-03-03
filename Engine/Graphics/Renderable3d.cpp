#include "Renderable3d.h"

#include "Vertex.h"

#include "../Libraries/glm/gtc/matrix_transform.hpp"

Renderable3d::Renderable3d(glm::vec3 position, glm::vec3 scale)
	: Position(position), Scale(scale), Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{	
	float vertices[24] = {
					  -1.000000, -1.000000,  1.000000,
					  -1.000000, -1.000000, -1.000000,
					   1.000000, -1.000000, -1.000000,
					   1.000000, -1.000000,  1.000000,
					  -1.000000,  1.000000,  1.000000,
					  -1.000000,  1.000000, -1.000000,
					   1.000000,  1.000000, -1.000000,
					   1.000000,  1.000000,  1.000000
	};

	unsigned int indices[36] = {
		1, 3, 0,
		7, 5, 4,
		4, 1, 0,
		5, 2, 1,
		2, 7, 3,
		0, 7, 4,
		1, 2, 3,
		7, 6, 5,
		4, 5, 1,
		5, 6, 2,
		2, 6, 7,
		0, 3, 7
	};

	Vertex vertex;
	vertex.PushFloat(3);

	p_Buffer = new Buffer(vertices, 8 * 3 * sizeof(float), vertex, GL_STATIC_DRAW);
	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 36, GL_STATIC_DRAW);
	p_Program = new Program();
}

Renderable3d::~Renderable3d()
{
	delete p_ElementArrayBuffer;
	delete p_Program;
	delete p_Buffer;
}

void Renderable3d::Draw(const glm::mat4 & view_projection)
{
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();
	p_Program->Bind();

	glm::mat4 LocationMat = glm::translate(view_projection, glm::vec3(Position.x, Position.y, Position.z));
	glm::mat4 RotationMat = glm::rotate(LocationMat, Rotation.z, glm::vec3(0.5f, 1.0f, 0.5f));
	glm::mat4 ScaleMat = glm::scale(RotationMat, glm::vec3(Scale.x, Scale.y, Scale.z));

	p_Program->SetUniformMat4f("u_MVP", ScaleMat);
	p_Program->SetUniform4f("u_Color", Color);
	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}
