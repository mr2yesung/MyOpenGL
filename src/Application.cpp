#include <GL/glew.h>
#include "Window.h"

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <gtc/type_ptr.hpp>

const unsigned int SCREENHEIGHT = 900;
const unsigned int SCREENWIDTH = 900;

int main(void)
{
    Window window(SCREENHEIGHT, SCREENWIDTH, "My OpenGL");

    if (window.Init())
        return -1;

    /* Initialize GLEW entry points after creating valid OpenGL rendering context */
    if (glewInit() != GLEW_OK)
        std::cout << "Error GLEW" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    
    const float vertex[24] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    const unsigned int indices[36] = {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Back face
        4, 5, 6,
        6, 7, 4,
        // Left face
        0, 3, 7,
        7, 4, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Top face
        3, 2, 6,
        6, 7, 3,
        // Bottom face
        0, 1, 5,
        5, 4, 0
    };

    const VertexArray va;
    const VertexBuffer vb(vertex, 24 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(3, GL_FLOAT, GL_FALSE);
    va.AddBuffer(vb, layout);

    const IndexBuffer ib(indices, 36);

    Shader shader("resources/shaders/CameraView.shader");

    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    const Renderer renderer;

    /* Loop until the user closes the window */
    while (!window.GetWindowCloseFlag())
    {
        /* Render here */
        renderer.Clear();

        shader.Bind();

        shader.SetUniformMatrix4fv("projection", GL_FALSE, glm::value_ptr(window.GetProjectionMatrix()));

        shader.SetUniformMatrix4fv("view", GL_FALSE, glm::value_ptr(window.GetCamera().GetViewMatrix()));

        renderer.Draw(va, ib);

        va.Unbind();
        ib.Unbind();

        window.SwapBuffers();

        window.PollEvents();
    }

    return 0;
}