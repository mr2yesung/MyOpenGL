#include <GL/glew.h>
#include "Window.h"

#include <iostream>

#include "Renderer.h"
#include "Shader.h"

#include <gtc/type_ptr.hpp>

#include "UIRenderer.h"

#include "FileBrowser.h"
#include "ModelLoader.h"

#include "Texture.h"

int main(void)
{
    Window window(900, 900, "OBJ Viewer");

    if (window.Init())
        return -1;

    /* Initialize GLEW entry points after creating valid OpenGL rendering context */
    if (glewInit() != GLEW_OK)
        std::cout << "Error GLEW" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    Renderer renderer;

    Texture texture;
    texture.Unbind();

    Shader shader("resources/shaders/Shader.shader");
    shader.Unbind();

    UIRenderer uiRenderer(window.GetGLFWWindow());

    // obj file opener
    UIComponent objExplorerUI("OBJ File Opener", ImVec2(100, 100), ImVec2(250, 75));
    objExplorerUI.PushText("Open 3d model file in .obj format");
    objExplorerUI.PushButton("Browse", [&renderer]() {
        std::string filePath = FileBrowser::BrowseFiles("obj 3D Models (*.obj)\0*.obj\0", "obj");
        std::vector<float> vertex;
        std::vector<unsigned int> indices;
        if (ModelLoader::LoadObjModel(filePath, vertex, indices))
        {
            renderer.LoadModel(vertex, indices);
        }
    });

    uiRenderer.Push(objExplorerUI);

    // png file opener
    UIComponent pngExplorerUI("Texture File Opener", ImVec2(100, 200), ImVec2(250, 75));
    pngExplorerUI.PushText("Open texture file");
    pngExplorerUI.PushButton("Browse", [&texture]() {
        std::string filePath = FileBrowser::BrowseFiles("textures (*.png, *.jpg)\0*.png;*.jpg\0", "png");
        texture.LoadTexture(filePath.c_str());
    });

    uiRenderer.Push(pngExplorerUI);

    /* Loop until the user closes the window */
    while (!window.GetWindowCloseFlag())
    {
        /* Render here */
        renderer.Clear();

        texture.Bind();
        shader.Bind();

        shader.SetUniformMatrix4fv("projection", GL_FALSE, glm::value_ptr(window.GetProjectionMatrix()));

        shader.SetUniformMatrix4fv("view", GL_FALSE, glm::value_ptr(window.GetCamera().GetViewMatrix()));

        shader.SetUniform1i("texture2d", 0);

        renderer.Draw();

        uiRenderer.Render();

        texture.Unbind();
        shader.Unbind();

        window.SwapBuffers();

        window.PollEvents();
    }

    return 0;
}