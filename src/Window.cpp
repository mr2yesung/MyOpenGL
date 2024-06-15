#include "Window.h"

#include <iostream>

Window* Window::instance = nullptr;

Window::Window(const unsigned int height, const unsigned int width, const char* name)
	:window(nullptr), height(height), width(width), name(name), mousePosition{0.0f, 0.0f}, camera()
{
    instance = this;
}

Window::~Window()
{
	glfwTerminate();
    std::cout << "Closed GLFW window." << std::endl;
}

/* https://www.glfw.org/documentation.html */
// returns 0 only when there were no problems on creating glfw window
const int Window::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "My OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, &Window::HandleFrameBufferSizeChange);

    glfwSetMouseButtonCallback(window, &Window::HandleMouseButtonClick);
    glfwSetCursorPosCallback(window, &Window::HandleMouseMove);
    glfwSetScrollCallback(window, &Window::HandleMouseScroll);

    return 0;
}

void Window::SwapBuffers()
{
    /* Swap front and back buffers */
    // prevent flickering through drawing on back buffer and displaying front buffer
    glfwSwapBuffers(window);
}

void Window::PollEvents()
{
    ProcessInput();
    /* Poll for and process events */
    glfwPollEvents();
}

// screen size callback
void Window::HandleFrameBufferSizeChange(GLFWwindow* window, int width, int height)
{
    if (instance)
    {
        glViewport(0, 0, width, height);
        instance->height = height;
        instance->width = width;
    }
}

// mouse callback
void Window::HandleMouseButtonClick(GLFWwindow* window, int button, int action, int mods)
{
    if (instance)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (action == GLFW_PRESS)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            else if (action == GLFW_RELEASE)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void Window::HandleMouseMove(GLFWwindow* window, double xPos, double yPos)
{
    if (instance)
    {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            const float deltaX = static_cast<float>(xPos) - instance->mousePosition.xPos;
            const float deltaY = instance->mousePosition.yPos - static_cast<float>(yPos);
            instance->camera.RotateCamera(deltaX, deltaY);
        }

        instance->mousePosition.xPos = static_cast<float>(xPos);
        instance->mousePosition.yPos = static_cast<float>(yPos);
    }
}

void Window::HandleMouseScroll(GLFWwindow* window, double xScroll, double yScroll)
{
    if (instance)
        instance->camera.ScrollCamera(static_cast<float>(yScroll));
}

// keyboard press
void Window::ProcessInput()
{
    // close glfw window when esc press
    if (GetKeyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (GetKeyPressed(GLFW_KEY_W))
        camera.MoveCamera(MovementDirection::FORWARD);
    if (GetKeyPressed(GLFW_KEY_S))
        camera.MoveCamera(MovementDirection::BACKWARD);
    if (GetKeyPressed(GLFW_KEY_A))
        camera.MoveCamera(MovementDirection::LEFT);
    if (GetKeyPressed(GLFW_KEY_D))
        camera.MoveCamera(MovementDirection::RIGHT);
}
