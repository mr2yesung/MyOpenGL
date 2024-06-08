#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib) const;
};