#pragma once

#include <vector>
#include <functional>
#include <variant>

#include <imgui.h>

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

	// using variant allows to hold several types of elements
	std::vector<std::variant<Button, Text>> elements;
public:
	UIComponent(const char* title, const ImVec2& position, const ImVec2& size);

	void Render();

	void PushButton(const char* label, std::function<void()> callback);
	void PushText(const char* content);
private:
	const bool CreateStart() const;
	void CreateEnd() const;
};