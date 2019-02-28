#pragma once

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

class Buffer
{
public:
	Buffer(const void* data, unsigned int size, GLenum usage);
	~Buffer();

	void Bind() const;
private:
	unsigned int m_BufferID;
};

