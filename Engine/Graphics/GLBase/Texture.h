#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();
	unsigned char* m_LocalBuffer;
	void Bind(unsigned slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_nWidth; }
	inline int GetHeight() const { return m_nHeight; }
	inline unsigned GetID() const { return m_TextureID; }

private:
	unsigned m_TextureID;
	int m_nWidth;
	int m_nHeight;
	int m_nBPP;
	std::string m_FilePath;
};

