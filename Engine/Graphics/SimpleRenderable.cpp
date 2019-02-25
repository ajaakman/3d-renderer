#include "SimpleRenderable.h"

SimpleRenderable::SimpleRenderable(float positionX, float positionY, float sizeX, float sizeY, int centered)
{
	if (centered)
	{
		positionX -= sizeX / 2;
		positionY -= sizeY / 2;
	}

	float positions[8] = {
			        positionX,         positionY,
			sizeX + positionX,         positionY,
			sizeX + positionX, sizeY + positionY,
			        positionX, sizeY + positionY
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
	p_Program->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
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

void SimpleRenderable::SetColor(float r, float b, float g, float a)
{
	p_Program->Bind();
	p_Program->SetUniform4f("u_Color", r, g, b, a);
}
