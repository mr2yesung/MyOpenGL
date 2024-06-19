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

			// button
			if (std::holds_alternative<Button>(element))
			{
				auto& button = std::get<Button>(element);
				if (ImGui::Button(button.label))
					button.callback();
			}

			// text
			else if (std::holds_alternative<Text>(element))
			{
				auto& text = std::get<Text>(element);
				ImGui::Text(text.content);
			}

			// color picker
			else if (std::holds_alternative<ColorPicker>(element))
			{
				auto& colorPicker = std::get<ColorPicker>(element);
				float color[3] = { colorPicker.color.r, colorPicker.color.g, colorPicker.color.b };
				// true when value is changed
				if (ImGui::ColorPicker3(colorPicker.label, color))
					colorPicker.color = glm::vec3(color[0], color[1], color[2]);
			}

			// float slider
			else if (std::holds_alternative<FloatSlider>(element))
			{
				auto& floatSlider = std::get<FloatSlider>(element);
				ImGui::SliderFloat(floatSlider.label, floatSlider.value, floatSlider.minValue, floatSlider.maxValue);
			}

			// space
			else if (std::holds_alternative<Space>(element))
			{
				auto& space = std::get<Space>(element);
				ImGui::Dummy(ImVec2(0.0f, space.size));
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

void UIComponent::PushColorPicker3(const char* label, glm::vec3& color)
{
	elements.push_back(ColorPicker{ label, color });
}

void UIComponent::PushFloatSlider(const char* label, float* value, const float minValue, const float maxValue)
{
	elements.push_back(FloatSlider{ label, value, minValue, maxValue });
}

void UIComponent::PushSpace(const float size)
{
	elements.push_back(Space{ size });
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
