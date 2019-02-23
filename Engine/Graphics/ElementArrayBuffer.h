#pragma once
class ElementArrayBuffer
{
private:
	unsigned int m_ArrayBufferID;
	unsigned int m_Count;
public:
	ElementArrayBuffer(const unsigned int* data, unsigned int count);
	~ElementArrayBuffer();

	void Bind() const;

	unsigned int GetCount() const;
};

