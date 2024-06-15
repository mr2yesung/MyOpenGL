#pragma once

class IndexBuffer
{
private:
	unsigned int indexBufferObject;
	unsigned int indicesCount;
public:
	IndexBuffer(const unsigned int* data, const unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline const unsigned int GetCount() const { return indicesCount; }
};