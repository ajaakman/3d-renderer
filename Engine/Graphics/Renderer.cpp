#include "Renderer.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include "../Utility/Error.h"

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
