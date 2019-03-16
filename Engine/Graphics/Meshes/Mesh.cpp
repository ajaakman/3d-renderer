#include "Mesh.h"

Mesh::Mesh(Primitive primitive)	
{
	switch (primitive)
	{
	case CUBE:
		{
			Cube mesh;
			VertexLayout vertex;
			for (auto & element : mesh.layout)
				vertex.PushFloat(element);

			p_Buffer = new Buffer(&mesh.vertices[0], mesh.vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
			p_ElementArrayBuffer = new ElementArrayBuffer(&mesh.indices[0], mesh.indices.size(), GL_STATIC_DRAW);
			p_Program = new Program("Resources/Shaders/Basic.shader");
			break;
		}
	case SPRITE:
		{
			Sprite mesh;
			VertexLayout vertex;
			for (auto & element : mesh.layout)
				vertex.PushFloat(element);

			p_Buffer = new Buffer(&mesh.vertices[0], mesh.vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
			p_ElementArrayBuffer = new ElementArrayBuffer(&mesh.indices[0], mesh.indices.size(), GL_STATIC_DRAW);
			p_Program = new Program("Resources/Shaders/Basic.shader");
			break;
		}
	}
}

Mesh::~Mesh()
{
	delete p_Buffer;
	delete p_ElementArrayBuffer;
	delete p_Program;
}

void Mesh::Draw(std::vector<Renderable*> renderables, Camera* camera, glm::vec3 light)
{
	p_Buffer->Bind();
	p_ElementArrayBuffer->Bind();
	p_Program->Bind();

	for (auto & renderable : renderables)
	{
		renderable->GetMaterial()->Use(p_Program, camera->GetMatrix(), camera->GetPosition(), light);
		GL(glDrawElements(GL_TRIANGLES, p_ElementArrayBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}
