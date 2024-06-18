#pragma once

#include <vector>

struct VertexBufferLayoutElement
{
	unsigned int size;
	unsigned char normalized;
	unsigned int offset;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferLayoutElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout();

	void Push(const unsigned int size, const unsigned char normalized);

	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return elements; }
	inline const unsigned int GetStride() const { return stride; }
};