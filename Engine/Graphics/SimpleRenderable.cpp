#include "SimpleRenderable.h"


SimpleRenderable::SimpleRenderable(float positionX)
{
	float positions[8] = {
			-0.1f + positionX, -0.1f,
			 0.1f + positionX, -0.1f,
			 0.1f + positionX,  0.1f,
			-0.1f + positionX,  0.1f,
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	p_VertexArray = new VertexArray;
	p_Buffer = new Buffer(positions, 4 * 2 * sizeof(float));

	Vertex vertex;
	vertex.PushFloat(2);
	p_VertexArray->AddBuffer(*p_Buffer, vertex);

	p_ElementArrayBuffer = new ElementArrayBuffer(indices, 6);

	p_Program = new Program("../Resources/Shaders/Basic.shader");
	p_Program->Bind();
	p_Program->SetUniform4f("u_Color", 0.8f, 0.4f, 0.8f, 1.0f);
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

void SimpleRenderable::UpdateUniforms(float color)
{
	p_Program->Bind();
	p_Program->SetUniform4f("u_Color", color, 0.4f, 0.8f, 1.0f);

	p_VertexArray->Bind();
	p_ElementArrayBuffer->Bind();
}
