#pragma once

#include <vector>

#include <GL/glew.h>

#include "../Utility/Error.h"


class Vertex
{
public:
	struct VertexElement
	{
		unsigned int count;
		unsigned int type;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
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

	Vertex();
	
	void PushFloat(unsigned int count);
	void PushUInt(unsigned int count);		
	void PushChar(unsigned int count);

	const std::vector<VertexElement> GetElements() const&;
	unsigned int GetStride() const;

private:

	std::vector<VertexElement> m_Elements;
	unsigned int m_Stride;
};

