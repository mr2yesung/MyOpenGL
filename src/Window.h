#pragma once

#include <GLFW/glfw3.h>

#include "Camera.h"

struct MousePosition {
	float xPos;
	float yPos;
};

class Window {
private:
	// prevent static function calls without instance
	static Window* instance;

	GLFWwindow* window;

	unsigned int height;
	unsigned int width;
	const char* name;

	MousePosition mousePosition;

	Camera camera;
public:
	Window(const unsigned int height = 900, const unsigned int width = 900, const char* name = "My OpenGL");
	~Window();

	const int Init();

	void SwapBuffers();
	void PollEvents();

	inline const int GetWindowCloseFlag() const { return glfwWindowShouldClose(window); }

	inline const Camera& GetCamera() const { return camera; }

	inline const glm::mat4 GetProjectionMatrix() const { return glm::perspective(glm::radians(camera.GetCameraZoom()), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f); }

	inline GLFWwindow* GetGLFWWindow() const { return window; }
private:
	// screen size callback
	static void HandleFrameBufferSizeChange(GLFWwindow* window, int width, int height);

	// mouse callback
	static void HandleMouseButtonClick(GLFWwindow* window, int button, int action, int mods);
	static void HandleMouseMove(GLFWwindow* window, double xPos, double yPos);
	static void HandleMouseScroll(GLFWwindow* window, double xScroll, double yScroll);

	// keyboard press
	void ProcessInput();
	inline const bool GetKeyPressed(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }
};
