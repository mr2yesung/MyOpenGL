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

#include "Lighting.h"

int main(void)
{
    Window window(1024, 1600, "OBJ Viewer");

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

    Lighting lighting;

    UIRenderer uiRenderer(window.GetGLFWWindow());

    // obj file opener
    UIComponent objExplorerUI("OBJ File Opener", ImVec2(50, 50), ImVec2(250, 75));
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

    // png file opener
    UIComponent pngExplorerUI("Texture File Opener", ImVec2(50, 150), ImVec2(250, 75));
    pngExplorerUI.PushText("Open texture file");
    pngExplorerUI.PushButton("Browse", [&texture]() {
        std::string filePath = FileBrowser::BrowseFiles("textures (*.png, *.jpg)\0*.png;*.jpg\0", "png");
        texture.LoadTexture(filePath.c_str());
    });

    // lighting settings
    UIComponent lightingUI("Lighting Settings", ImVec2(350, 50), ImVec2(400, 300));
    glm::vec3& lightDir = lighting.getLightDir();
    glm::vec3& lightColor = lighting.getLightColor();
    float& ambientStrength = lighting.getAmbientStrength();
    // light direction
    lightingUI.PushText("Light Direction");
    lightingUI.PushFloatSlider("x", &lightDir.x);
    lightingUI.PushFloatSlider("y", &lightDir.y);
    lightingUI.PushFloatSlider("z", &lightDir.z);
    // light color
    lightingUI.PushSpace(20.f);
    lightingUI.PushColorPicker3("Light Color", lightColor);
    // ambient strength
    lightingUI.PushSpace(20.f);
    lightingUI.PushFloatSlider("Ambient Strength", &ambientStrength, 0.0f, 1.0f);

    uiRenderer.Push(objExplorerUI);
    uiRenderer.Push(pngExplorerUI);
    uiRenderer.Push(lightingUI);

    /* Loop until the user closes the window */
    while (!window.GetWindowCloseFlag())
    {
        /* Render here */
        renderer.Clear();

        texture.Bind();
        shader.Bind();

        // camera view uniforms
        shader.SetUniformMatrix4fv("projection", GL_FALSE, glm::value_ptr(window.GetProjectionMatrix()));
        shader.SetUniformMatrix4fv("view", GL_FALSE, glm::value_ptr(window.GetCamera().GetViewMatrix()));

        // texture uniform
        shader.SetUniform1i("texture2d", 0);

        // lighting uniforms
        shader.SetUniform3f("lightDirection", lightDir.x, lightDir.y, lightDir.z);
        shader.SetUniform3f("lightColor", lightColor.r, lightColor.g, lightColor.b);
        shader.SetUniform1f("ambientStrength", ambientStrength);

        renderer.Draw();

        uiRenderer.Render();

        texture.Unbind();
        shader.Unbind();

        window.SwapBuffers();

        window.PollEvents();
    }

    return 0;
}