#pragma once

#include <string>
#include <unordered_map>

#include "../GLBase/Texture.h"

class TextureCache
{
public:
	static Texture* UseTexture(std::string path);
	static void DeleteTexture(Texture* texture);
private:
	static std::unordered_map<std::string, Texture*> m_TextureCache;
};

