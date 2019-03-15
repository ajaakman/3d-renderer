#include "Mesh.h"

Mesh::Mesh(Primitive primitive)	
{
	switch (primitive)
	{
	case CUBE:
		{
			Cube cube;
			VertexLayout vertex;
			for (auto & element : cube.layout)
				vertex.PushFloat(element);

			p_Buffer = new Buffer(&cube.vertices[0], cube.vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
			p_ElementArrayBuffer = new ElementArrayBuffer(&cube.indices[0], cube.indices.size(), GL_STATIC_DRAW);
			p_Program = new Program("Resources/Shaders/Basic.shader");
			break;
		}
	case SPRITE:
		{
			Sprite sprite;
			VertexLayout vertex;
			for (auto & element : sprite.layout)
				vertex.PushFloat(element);

			p_Buffer = new Buffer(&sprite.vertices[0], sprite.vertices.size() * sizeof(float), vertex, GL_STATIC_DRAW);
			p_ElementArrayBuffer = new ElementArrayBuffer(&sprite.indices[0], sprite.indices.size(), GL_STATIC_DRAW);
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
