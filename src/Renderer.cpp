#include "Renderer.h"

#include <GL/glew.h>

Renderer::Renderer()
    :va(), vb(nullptr), layout(), ib(nullptr)
{
    layout.Push(3, GL_FALSE);
    layout.Push(3, GL_FALSE);
    layout.Push(2, GL_FALSE);
}

Renderer::~Renderer()
{
    DeleteBuffer();
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw() const
{
    if (vb && ib)
    {
        va.Bind();
	    ib->Bind();

	    glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);

	    va.Unbind();
	    ib->Unbind();
    }
}

void Renderer::LoadModel(const std::vector<float>& vertex, const std::vector<unsigned int>& indices)
{
    DeleteBuffer();

    vb = new VertexBuffer(vertex.data(), vertex.size() * sizeof(float));
    ib = new IndexBuffer(indices.data(), indices.size());

    va.AddBuffer(*vb, layout);

    va.Unbind();
    vb->Unbind();
    ib->Unbind();
}

void Renderer::DeleteBuffer()
{
    if (vb)
        delete vb;
    if (ib)
        delete ib;
}
