#include "VertexBufferLayout.h"

#include <GL/glew.h>
#include <iostream>

VertexBufferLayout::VertexBufferLayout()
	:stride(0)
{
}

void VertexBufferLayout::Push(const unsigned int size, const unsigned int type, const unsigned char normalized)
{
	elements.push_back({ size, type, normalized, stride });
	stride += size * GetTypeSize(type);
}

const unsigned int VertexBufferLayout::GetTypeSize(const unsigned int type) const
{
	switch (type)
	{
	case GL_FLOAT: return 4;
	case GL_UNSIGNED_INT: return 4;
	case GL_UNSIGNED_BYTE: return 1;
	}

	std::cout << "Attribute not supported type" << std::endl;
	return 0;
}