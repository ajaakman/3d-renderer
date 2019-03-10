#pragma once

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <vector>

#include "../../Utility/Error.h"

class VertexLayout
{
public:
	struct VertexElement
	{
		unsigned count;
		unsigned type;
		unsigned char normalized;

		static unsigned GetSizeOfType(unsigned type)
		{
			switch (type)
			{
			case GL_FLOAT:			 return 4;
			case GL_UNSIGNED_INT:	 return 4;
			case GL_UNSIGNED_BYTE:	 return 1;
			}
			ASSERT(false);
			return 0;
		}
	};

	VertexLayout();
	
	void PushFloat(unsigned count);
	void PushUInt(unsigned count);		
	void PushChar(unsigned count);

	const std::vector<VertexElement> GetElements() const&;
	unsigned GetStride() const;

private:

	std::vector<VertexElement> m_Elements;
	unsigned m_Stride;
};

