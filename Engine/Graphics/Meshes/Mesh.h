#pragma once

#include "Primitives.h"
#include "../GLBase/Buffer.h"
#include "../GLBase/ElementArrayBuffer.h"
#include "../GLBase/Program.h"
#include "../GLBase/Texture.h"
#include "../Renderables/Renderable.h"
#include "../Cameras/Camera.h"

class Mesh
{
public:
	enum Primitive { SPRITE= 0, CUBE};

	Mesh(Primitive primitive);
	~Mesh();

	void Draw(std::vector<Renderable*> renderables, Camera* camera, glm::vec3 light);

private:

	ElementArrayBuffer* p_ElementArrayBuffer;
	Program* p_Program;
	Buffer* p_Buffer;
};

