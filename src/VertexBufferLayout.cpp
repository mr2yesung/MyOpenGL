#include "VertexBufferLayout.h"

#include <GL/glew.h>
#include <iostream>

VertexBufferLayout::VertexBufferLayout()
	:stride(0)
{
}

void VertexBufferLayout::Push(const unsigned int size, const unsigned char normalized)
{
	elements.push_back({ size, normalized, stride });
	stride += size * sizeof(float);
}