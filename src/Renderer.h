#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class Renderer
{
private:
	VertexArray va;
	VertexBuffer* vb;
	VertexBufferLayout layout;
	IndexBuffer* ib;
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw() const;

	void LoadModel(const std::vector<float>& vertex, const std::vector<unsigned int>& indices);
private:
	void DeleteBuffer();
};
