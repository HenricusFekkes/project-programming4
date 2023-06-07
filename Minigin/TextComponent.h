#pragma once

#include "Component.h"
#include <memory>
#include <string>

namespace dae {
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent final: public Component
	{
	public:
		explicit TextComponent(GameObject* pGameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
	private:
		std::string m_text{ " " };
		std::shared_ptr<Font> m_font{};
		RenderComponent* m_pRenderComponent{};
		bool m_needsUpdate{};
	};
}

