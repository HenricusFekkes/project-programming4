#pragma once

#include "IComponent.h"
#include <memory>
#include <string>

namespace dae {
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent final: public IComponent
	{
	public:
		explicit TextComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
	private:
		std::string m_Text{ " " };
		std::shared_ptr<Font> m_Font{};
		bool m_NeedsUpdate{};
	};
}

