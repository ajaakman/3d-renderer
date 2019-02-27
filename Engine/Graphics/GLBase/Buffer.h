#pragma once

class Buffer
{
public:
	Buffer(const void* data, unsigned int size);
	~Buffer();

	void Bind() const;
private:
	unsigned int m_BufferID;
};

