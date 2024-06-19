#pragma once

#include <vector>
#include <functional>
#include <variant>

#include <imgui.h>

#include <glm.hpp>

class UIComponent {
private:
	const char* title;
	const ImVec2 position;
	const ImVec2 size;

	struct Button {
		const char* label;
		std::function<void()> callback;
	};

	struct Text {
		const char* content;
	};

	struct ColorPicker {
		const char* label;
		glm::vec3& color;
	};

	struct FloatSlider {
		const char* label;
		float* value;
		const float minValue;
		const float maxValue;
	};

	struct Space {
		const float size;
	};

	// using variant allows to hold several types of elements
	std::vector<std::variant<Button, Text, ColorPicker, FloatSlider, Space>> elements;
public:
	UIComponent(const char* title, const ImVec2& position, const ImVec2& size);

	void Render();

	void PushButton(const char* label, std::function<void()> callback);
	void PushText(const char* content);
	void PushColorPicker3(const char* label, glm::vec3& color);
	void PushFloatSlider(const char* label, float* value, const float minValue = -1.f, const float maxValue = 1.f);
	void PushSpace(const float size);
private:
	const bool CreateStart() const;
	void CreateEnd() const;
};