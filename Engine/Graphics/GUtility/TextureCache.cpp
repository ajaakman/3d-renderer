#include "TextureCache.h"
#include <iostream>

std::unordered_map<std::string, Texture*> TextureCache::m_TextureCache;

Texture* TextureCache::UseTexture(const std::string & path)
{
	auto it = m_TextureCache.find(path);

	if (it == m_TextureCache.end())
	{
		Texture* texture = new Texture(path);
		m_TextureCache.emplace(path, texture);
		return texture;
	}
	else
	{
		return it->second;
	}
}

void TextureCache::DeleteTexture(Texture * texture)
{
	//TODO
}
