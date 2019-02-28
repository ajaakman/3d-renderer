#include "SimpleRenderable.h"
#include "../Libraries/glm/gtc/matrix_transform.hpp"

SimpleRenderable::SimpleRenderable(glm::vec2 position, glm::vec2 size, int centered)
{
	if (centered)
	{
		position.x -= size.x / 2;
		position.y -= size.y / 2;
	}

	float positions[8] = {
					 position.x,          position.y,
			size.x + position.x,          position.y,
			size.x + position.x, size.y + position.y,
				 	 position.x, size.y + position.y
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
	p_Program->SetUniform4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::mat4 Projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	p_Program->SetUniformMat4f("u_MVP", Projection);
}

void SimpleRenderable::Draw()
{
	p_Program->Bind();
	p_VertexArray->Bind();
	p_ElementArrayBuffer->Bind();
	GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

SimpleRenderable::~SimpleRenderable()
{
}

void SimpleRenderable::SetColor(glm::vec4 color)
{
	p_Program->Bind();
	p_Program->SetUniform4f("u_Color", color);
}

void SimpleRenderable::SetPosition(glm::vec2 position)
{
	p_Program->Bind();
	glm::mat4 Projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0));
	glm::mat4 MVP = Projection * View * Model;
	p_Program->SetUniformMat4f("u_MVP", MVP);
}
