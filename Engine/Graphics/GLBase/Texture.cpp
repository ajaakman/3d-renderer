#include "Texture.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>

#include "../../Utility/Error.h"
#include "../../Libraries/stbi/stbi.h"

Texture::Texture(const std::string & path)
	: m_TextureID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_nWidth(0), m_nHeight(0), m_nBPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &m_nBPP, 4);

	GL(glGenTextures(1, &m_TextureID));
	GL(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (m_LocalBuffer != nullptr)
	{
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	}
	else
	{
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		std::cout << "Texture: " << path << " failed to load.\n";
		unsigned char LocalBuffer[64] =
		{
			215, 0,  215, 255,
			40,  40, 40,  255, 
			215, 0,  215, 255,
			40,  40, 40,  255, 
			40,  40, 40,  255,
			215, 0,  215, 255,
			40,  40, 40,  255,
			215, 0,  215, 255,
			215, 0,  215, 255,
			40,  40, 40,  255,
			215, 0,  215, 255,
			40,  40, 40,  255,
			40,  40, 40,  255,
			215, 0,  215, 255,
			40,  40, 40,  255,
			215, 0,  215, 255
		};
		GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));
	}

	GL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GL(glDeleteTextures(1, &m_TextureID));
}

void Texture::Bind(unsigned int slot) const
{
	GL(glActiveTexture(GL_TEXTURE0 + slot));
	GL(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Unbind() const
{
	GL(glBindTexture(GL_TEXTURE_2D, 0));
}