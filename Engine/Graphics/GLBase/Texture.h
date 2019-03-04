#pragma once

class Texture
{
private:
	unsigned int m_TextureID;
	int m_nWidth;
	int m_nHeight;
public:
	Texture();
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_nWidth; }
	inline int GetHeight() const { return m_nHeight; }
};

