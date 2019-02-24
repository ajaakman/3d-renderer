#include "Renderer.h"

#include "../Utility/Error.h"

#include "GL/glew.h"

Renderer::Renderer()
{	
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT));
}
