#include "VertexBufferLayout.h"

#include <GL/glew.h>
#include <iostream>

VertexBufferLayout::VertexBufferLayout()
	:stride(0)
{
}

void VertexBufferLayout::Push(unsigned int size, unsigned int type, unsigned char normalized)
{
	elements.push_back({ size, type, normalized, stride });
	stride += size * GetTypeSize(type);
}

unsigned int VertexBufferLayout::GetTypeSize(unsigned int type) const
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