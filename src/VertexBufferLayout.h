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

	void Push(const unsigned int size, const unsigned int type, const unsigned char normalized);

	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return elements; }
	inline const unsigned int GetStride() const { return stride; }
private:
	const unsigned int GetTypeSize(const unsigned int type) const;
};