#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include "UIComponent.h"

class UIRenderer {
private:
	std::vector<UIComponent> uiComponents;
public:
	UIRenderer(GLFWwindow* window);
	~UIRenderer();

	void Render();
	void Push(const UIComponent& component);
};