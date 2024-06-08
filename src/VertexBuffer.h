#pragma once

class VertexBuffer
{
private:
	unsigned int buffer;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};