#include "SimpleRenderable.h"

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
