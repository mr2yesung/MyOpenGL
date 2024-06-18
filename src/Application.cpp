#include <GL/glew.h>
#include "Window.h"

#include <iostream>

#include "Renderer.h"
#include "Shader.h"

#include <gtc/type_ptr.hpp>

#include "UIRenderer.h"

#include "FileBrowser.h"
#include "ModelLoader.h"

int main(void)
{
    Window window(900, 900, "My OpenGL");

    if (window.Init())
        return -1;

    /* Initialize GLEW entry points after creating valid OpenGL rendering context */
    if (glewInit() != GLEW_OK)
        std::cout << "Error GLEW" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    Renderer renderer;

    Shader shader("resources/shaders/CameraView.shader");

    shader.Unbind();

    UIRenderer uiRenderer(window.GetGLFWWindow());

    UIComponent fileExplorerUI("File Opener", ImVec2(100, 100), ImVec2(250, 75));
    fileExplorerUI.PushText("Open 3d model file in .obj format");
    fileExplorerUI.PushButton("Browse", [&renderer]() {
        std::string filePath = FileBrowser::BrowseFiles("obj 3D Models\0*.obj\0", "obj");
        std::vector<float> vertex;
        std::vector<unsigned int> indices;
        if (ModelLoader::LoadObjModel(filePath, vertex, indices))
        {
            renderer.LoadModel(vertex, indices);
        }
    });

    uiRenderer.Push(fileExplorerUI);

    /* Loop until the user closes the window */
    while (!window.GetWindowCloseFlag())
    {
        /* Render here */
        renderer.Clear();

        shader.Bind();

        shader.SetUniformMatrix4fv("projection", GL_FALSE, glm::value_ptr(window.GetProjectionMatrix()));

        shader.SetUniformMatrix4fv("view", GL_FALSE, glm::value_ptr(window.GetCamera().GetViewMatrix()));

        renderer.Draw();

        uiRenderer.Render();

        window.SwapBuffers();

        window.PollEvents();
    }

    return 0;
}