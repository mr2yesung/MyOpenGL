#include "UIComponent.h"

UIComponent::UIComponent(const char* title, const ImVec2& position, const ImVec2& size)
	:title(title), position(position), size(size)
{
}

void UIComponent::Render()
{
	if (CreateStart())
	{
		for (auto& element : elements)
		{
			// holds_alternative checks whether the variant is currently holding type T
			// get retrieves the value of type T from the variant, throw std::bad_variant_access exception when the variant does not hold type T
			if (std::holds_alternative<Button>(element))
			{
				auto& button = std::get<Button>(element);
				if (ImGui::Button(button.label))
					button.callback();
			}
			else if (std::holds_alternative<Text>(element))
			{
				auto& text = std::get<Text>(element);
				ImGui::Text(text.content);
			}
		}
	}

	CreateEnd();
}

void UIComponent::PushButton(const char* label, std::function<void()> callback)
{
	elements.push_back(Button{ label, callback });
}

void UIComponent::PushText(const char* content)
{
	elements.push_back(Text{ content });
}

const bool UIComponent::CreateStart() const
{
	ImGui::SetNextWindowPos(position);
	ImGui::SetNextWindowSize(size);
	return ImGui::Begin(title);
}

void UIComponent::CreateEnd() const
{
	ImGui::End();
}
