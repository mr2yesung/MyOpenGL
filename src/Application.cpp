#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

/* https://www.glfw.org/documentation.html */
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1600, 900, "My OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* Initialize GLEW entry points after creating valid OpenGL rendering context */
    if (glewInit() != GLEW_OK)
        std::cout << "Error GLEW" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    {
        float vertex[20] = {
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 1.0f, 1.0f, 0.0f
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(vertex, 20 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(2, GL_FLOAT, GL_FALSE);
        layout.Push(3, GL_FLOAT, GL_FALSE);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("resources/shaders/ColorAttribute.shader");

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();

            renderer.Draw(va, ib);

            va.Unbind();
            ib.Unbind();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();

    return 0;
}

/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
glViewport(0, 0, width, height);
}
*/