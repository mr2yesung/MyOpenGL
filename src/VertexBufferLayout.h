#pragma once

#include <vector>

struct VertexBufferLayoutElement
{
	unsigned int size;
	unsigned int type;
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

	void Push(unsigned int size, unsigned int type, unsigned char normalized);

	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return elements; }
	inline unsigned int GetStride() const { return stride; }
private:
	unsigned int GetTypeSize(unsigned int type) const;
};