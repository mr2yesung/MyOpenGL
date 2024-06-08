#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vertexArrayObject);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();

	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.size, element.type, element.normalized, layout.GetStride(), (const void*)element.offset);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(vertexArrayObject);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
